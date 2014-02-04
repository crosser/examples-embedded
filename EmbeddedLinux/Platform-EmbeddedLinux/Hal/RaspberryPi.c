/*
 * ============ Hardware Abstraction Layer for Raspberry Pi ============
 */

/*

DESCRIPTION

    - an implementation of the Emmoco HAL for the Raspberry Pi SBC
    - the board's UART 0 serial port is used for communication
    - the board's GPIO 23 and GPIO 24 lines are used for handshaking
    - the board's GPIO 22 line may be used to switch an external LED

PLATFORM CONFIGURATION

    - configure your EDB firmware with factory default settings
    
    - connect your EDB to the Raspberry Pi board using your Em-Cable:
      
            BLACK   [GND]           -->     P1 PIN 6   [GND]     
            WHITE   [EAP_TX_ACK]    -->     P1 PIN 18  [GPIO 24]
            RED     [VCC]           -->     P1 PIN 17  [3v3 Power]
            BLUE    [EAP_TX]        -->     P1 PIN 8   [TXD]
            ORANGE  [EAP_RX]        -->     P1 PIN 10  [RXD]
            YELLOW  [EAP_RX_ACK]    -->     P1 PIN 16  [GPIO 23]

    - optionally connect an external LED driver using jumper wires:

            Ground                  -->     P1 PIN 14  [GND]
            LED signal (3v3)        -->     P1 PIN 15  [GPIO 22]

TOOLING ENVIRONMENT

    - GNU make, binutils, gcc (pre-installed on Raspberry Pi)
    - Java development kit:
          sudo apt-get install oracle-java7-jdk
    - Emmoco em-builder command line tool:
          sudo dpkg -i emmoco-tools-linux-all-*.deb
    
NOTES

    - developed against unmodified Raspbian Linux (3.6.11+ kernel)
    - copy the examples-lp/ file hierarchy to the Raspberry Pi SBC
    - build and execute on Raspberry Pi as root user:
    
         cd examples-lp/Blinker-EmbeddedLinux/
         make
         sudo ./Output/Blinker-Prog.out

LINKS

    - http://www.raspberrypi.org

*/

#include "Hal.h"

#include <fcntl.h> // for O_WRONLY
#include <termios.h> // for tcsetattr()
#include <sys/timerfd.h> // for timerfd

extern int ledFd;
extern int uartFd;
extern int rxAckFd;
extern int txAckFd;
extern int timerFd;

/* -------- APP-HAL INTERFACE -------- */

void Hal_init() {
    int sysFd;

    sysFd = open("/sys/class/gpio/export", O_WRONLY);
    if (sysFd < 0) {
        perror("open GPIO export");
        exit(-1);
    }
    write(sysFd, "22", 2); // export GPIO 22 to user space
    close(sysFd);

    sysFd = open("/sys/class/gpio/gpio22/direction", O_WRONLY);
    if (sysFd < 0) {
        perror("open GPIO22 direction");
        exit(-1);
    }
    write(sysFd, "out", 3); // use GPIO 22 for LED output
    close(sysFd);

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

    ledFd = open("/sys/class/gpio/gpio22/value", O_WRONLY); // open LED output
    if (ledFd < 0) {
        perror("open GPIO22");
        exit(-1);
    }

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

    uartFd = open("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NONBLOCK); // open serial UART 0
    if (uartFd < 0) {
        perror("open UART");
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

    if (-1 == tcsetattr(uartFd, TCSANOW, &attr)) { // set communication parameters
        perror("tcsetattr TCSANOW");
        exit(-1);
    }

    timerFd = timerfd_create(CLOCK_REALTIME, TFD_NONBLOCK); // create HAL tick timer
    if (timerFd < 0) {
        perror("timerfd_create");
        exit(-1);
    }

    printf("initialized\n");
}
