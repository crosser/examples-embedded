/*
 * ============ Hardware Abstraction Layer for Raspberry Pi ============
 */

/*

DESCRIPTION

    - an implementation of the Emmoco HAL for the Raspberry Pi SBC
    - the board's UART 0 serial port is used for communication
    - the board's GPIO 23 and GPIO 24 lines are used for handshaking
    
PLATFORM CONFIGURATION

    - configure your EDB firmware with factory default settings
    
    - connect your EDB to the Raspberry Pi board using your Em-Cable:
      
            BLACK   [GND]           -->     P1 PIN 6   [GND]     
            WHITE   [EAP_TX_ACK]    -->     P1 PIN 18  [GPIO 24]
            RED     [VCC]           -->     P1 PIN 17  [3v3 Power]
            BLUE    [EAP_TX]        -->     P1 PIN 8   [TXD]
            ORANGE  [EAP_RX]        -->     P1 PIN 10  [RXD]
            YELLOW  [EAP_RX_ACK]    -->     P1 PIN 16  [GPIO 23]
        
TOOLING ENVIRONMENT

    - GNU make, binutils, gcc (pre-installed on Raspberry Pi)
    - Java development kit: sudo apt-get install oracle-java7-jdk
    - Emmoco em-builder command line tool
    
NOTES

    - developed against unmodified Raspbian Linux (3.6.11+ kernel)
    - copy the examples-lp/ file hierarchy to the Raspberry Pi SBC
    - build and execute on Raspberry Pi as root user:
    
         cd examples-lp/Blinker-RaspberryPi/
         make
         sudo ./Output/Blinker-Prog.out

LINKS

    - http://www.raspberrypi.org

*/

#include "Hal.h"
#include "Em_Message.h"

#include <fcntl.h> // for fcntl()
#include <signal.h> // for sigaction()
#include <stddef.h> // for NULL
#include <stdlib.h> // for exit()
#include <stdint.h> // for uint8_t
#include <unistd.h> // for read()
#include <stdio.h> // for perror()
#include <termios.h> // for tcsetattr()
#include <pthread.h> // for POSIX threads
#include <poll.h> // for poll()
#include <errno.h> // for EINTR
#include <semaphore.h> // for semaphores
#include <sys/time.h> // for timers

struct itimerval tickTimer;
static Hal_Handler tickHandler;
static bool ledState;
static int uartFd;
static int rxAckFd;
static int txAckFd;
static pthread_t txAckThread;
static sem_t eventSem;
static sem_t txAckSem;

static volatile bool dispatchFlag;
static volatile bool tickFlag;

/* --------- I/O HANDLERS --------- */

static void Hal_timerHandler(void) {
    tickFlag = 1;
    sem_post(&eventSem);
}

static void Hal_rxHandler(void) {
    uint8_t b;

    if (1 != read(uartFd, &b, 1)) {
        return; // nothing to read
    }
    Em_Message_startRx();
    write(rxAckFd, "0", 1); // EAP_RX_ACK clear
    write(rxAckFd, "1", 1); // EAP_RX_ACK set
    if (Em_Message_addByte(b)) {
        dispatchFlag = 1;
        sem_post(&eventSem);
    }
}

static void Hal_txAckHandler (void *ptr) {
    int rc;
    struct pollfd pfd;
    uint8_t b;
    char buf[3];

    pfd.fd = txAckFd;
    pfd.events = POLLPRI;
    while (0 == sem_wait(&txAckSem)) {
        while (1) {
            lseek(txAckFd, 0, SEEK_SET);
            rc = poll(&pfd, 1, 10000);
            if (0 == rc) {
                printf("EAP_TX_ACK timeout\n");
            } else if (0 > rc) {
                if (EINTR != errno) { // we expect EINTR
                    perror("poll EAP_TX_ACK");
                }
            } else if (Em_Message_getByte(&b)) {
                read(txAckFd, buf, 3); // clear EAP_TX_ACK handler
                write(uartFd, &b, 1); // send a single byte
            } else { // no further bytes to send
                break;
            }
        }
    }
    printf("EAP_TX_ACK handler exiting\n");
}

/* -------- APP-HAL INTERFACE -------- */

void Hal_buttonEnable(Hal_Handler handler) {
}

void Hal_connected(void) {
    printf("connected\n");
}

void Hal_debugOn(uint8_t line) {
}

void Hal_debugOff(uint8_t line) {
}

void Hal_debugPulse(uint8_t line) {
}

void Hal_delay(uint16_t msecs) {
    usleep(msecs * 1000);
}

void Hal_disconnected(void) {
    printf("disconnected\n");
}

void Hal_init() {
    struct sigaction sigalrm_sa;
    struct sigaction sigio_sa;
    sigset_t sigalrm_mask;
    sigset_t sigio_mask;
    int sysFd;

    sem_init(&eventSem, 0, 0);
    sem_init(&txAckSem, 0, 0);

    sysFd = open("/sys/class/gpio/export", O_WRONLY);
    if (sysFd < 0) {
        perror("open GPIO export");
        exit(-1);
    }
    write(sysFd, "23", 2); // export GPIO 23 to user space
    close(sysFd);

    sysFd = open("/sys/class/gpio/gpio23/direction", O_WRONLY);
    if (sysFd < 0) {
        perror("open GPIO23 direction");
        exit(-1);
    }
    write(sysFd, "out", 3); // use GPIO 23 for EAP_RX_ACK output
    close(sysFd);

    sysFd = open("/sys/class/gpio/export", O_WRONLY);
    if (sysFd < 0) {
        perror("open GPIO export");
        exit(-1);
    }
    write(sysFd, "24", 2); // export GPIO 24 to user space
    close(sysFd);

    sysFd = open("/sys/class/gpio/gpio24/direction", O_WRONLY);
    if (sysFd < 0) {
        perror("open GPIO24 direction");
        exit(-1);
    }
    write(sysFd, "in", 2); // use GPIO 24 for EAP_TX_ACK input
    close(sysFd);

    sysFd = open("/sys/class/gpio/gpio24/edge", O_WRONLY);
    if (sysFd < 0) {
        perror("open GPIO24 edge");
        exit(-1);
    }
    write(sysFd, "falling", 7); // configure GPIO 24 for EAP_TX_ACK interrupt
    close(sysFd);

    rxAckFd = open("/sys/class/gpio/gpio23/value", O_WRONLY); // open EAP_RX_ACK output
    if (rxAckFd < 0) {
        perror("open GPIO23");
        exit(-1);
    }

    txAckFd = open("/sys/class/gpio/gpio24/value", O_RDONLY); // open EAP_TX_ACK input
    if (txAckFd < 0) {
        perror("open GPIO24");
        exit(-1);
    }

    uartFd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NONBLOCK); // open serial UART
    if (uartFd < 0) {
        perror("open UART");
        exit(-1);
    }

    sigemptyset(&sigio_mask);
    sigio_sa.sa_handler = (void *) Hal_rxHandler;
    sigio_sa.sa_mask = sigio_mask;
    sigio_sa.sa_flags = 0;
    sigio_sa.sa_restorer = NULL;
    if (-1 == sigaction(SIGIO, &sigio_sa, NULL)) { // set I/O signal handler
        perror("sigaction SIGIO");
        exit(-1);
    }

    sigemptyset(&sigalrm_mask);
    sigalrm_sa.sa_handler = (void *) Hal_timerHandler;
    sigalrm_sa.sa_mask = sigalrm_mask;
    sigalrm_sa.sa_flags = 0;
    sigalrm_sa.sa_restorer = NULL;
    if (-1 == sigaction(SIGALRM, &sigalrm_sa, NULL)) { // set alarm signal handler
        perror("sigaction SIGALRM");
        exit(-1);
    }

    struct termios attr;
    tcgetattr(uartFd, &attr);
    cfsetispeed(&attr, B115200); // 115200 baud out
    cfsetospeed(&attr, B115200); // 115200 baud in
    attr.c_cflag &= ~PARENB; // no parity bit
    attr.c_cflag &= ~CSTOPB; // 1 stop bit
    attr.c_cflag &= ~CSIZE; // clear word size
    attr.c_cflag |= CS8; // set 8 bit word size
    attr.c_cflag &= ~CRTSCTS; // no RTS/CTS handshaking
    attr.c_iflag = IGNBRK; // ignore break
    attr.c_lflag = 0;
    attr.c_oflag = 0;
    attr.c_cc[VTIME] = 0; // no wait on read
    attr.c_cc[VMIN] = 0; // no minimum read

    if (-1 == tcsetattr(uartFd, TCSANOW, &attr)) { // set communication parameters
        perror("tcsetattr TCSANOW");
        exit(-1);
    }

    if (-1 == fcntl(uartFd, F_SETOWN, getpid())) // set owner
    {
        perror("fcntl F_SETOWN");
        exit(-1);
    }

    const int flags = fcntl(uartFd, F_GETFL);
    if (-1 == fcntl(uartFd, F_SETFL, flags | FASYNC)) { // set asynchronous mode
        perror("fcntl F_SETFL");
        exit(-1);
    }

    pthread_create(&txAckThread, NULL, (void *) &Hal_txAckHandler, NULL); // create EAP_TX_ACK handler

    printf("initialized\n");
}

void Hal_idleLoop(void) {
    while (1) {
        if (0 == sem_wait(&eventSem)) { // wait for an event
            if (dispatchFlag) {
                dispatchFlag = 0;
                Em_Message_dispatch();
            } else if (tickFlag) {
                tickFlag = 0;
                (*tickHandler)();
            }
        }
    }
}

void Hal_ledOn(void) {
    ledState = 1;
    printf("LED on\n");
}

void Hal_ledOff(void) {
    ledState = 0;
    printf("LED off\n");
}

bool Hal_ledRead(void) {
    return ledState;
}

void Hal_ledToggle(void) {
    ledState = (ledState != 1);
    printf("LED toggle\n");
}

void Hal_tickStart(uint16_t msecs, void (*handler)(void)) {
    tickTimer.it_value.tv_sec = msecs / 1000;
    tickTimer.it_value.tv_usec = (msecs % 1000) * 1000;
    tickTimer.it_interval.tv_sec = msecs / 1000;
    tickTimer.it_interval.tv_usec = (msecs % 1000) * 1000;
    tickHandler = handler;
    setitimer(ITIMER_REAL, &tickTimer, NULL);
}

/* -------- SRT-HAL INTERFACE -------- */

uint8_t Em_Hal_lock(void) {
}

void Em_Hal_reset(void) {
    write(rxAckFd, "0", 1); // EAP_RX_ACK clear
    usleep(100000);
    write(rxAckFd, "1", 1); // EAP_RX_ACK set
    usleep(500000);
    write(rxAckFd, "0", 1); // EAP_RX_ACK clear
    usleep(100000);
    write(rxAckFd, "1", 1); // EAP_RX_ACK set
}

void Em_Hal_startSend(void) {
    char buf[3];
    read(txAckFd, buf, 3); // clear EAP_TX_ACK handler
    sem_post(&txAckSem); // start EAP_TX_ACK handler
    uint8_t b = Em_Message_startTx();
    write(uartFd, &b, 1); // send the initial byte
}

void Em_Hal_unlock(uint8_t key) {
}

void Em_Hal_watchOn(void) {
}

void Em_Hal_watchOff(void) {
}

