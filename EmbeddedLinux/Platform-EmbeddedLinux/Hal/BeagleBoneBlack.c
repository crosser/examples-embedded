/*
 * ============ Hardware Abstraction Layer for BeagleBone Black ============
 */

/*

DESCRIPTION

    - an implementation of the Emmoco HAL for the BeagleBone Black SBC
    - the board's UART1 serial port is used for communication
    - the board's GPIO2_2 and GPIO2_3 lines are used for handshaking
    - the board's GPIO2_4 line may be used to switch an external LED

PLATFORM CONFIGURATION

    - configure your EDB firmware with factory default settings
    
    - connect your EDB to the BeagleBone Black board using your Em-Cable:
      
            BLACK   [GND]           -->     P9 PIN 1   [DGND]  
            WHITE   [EAP_TX_ACK]    -->     P8 PIN 8   [GPIO2_3]
            RED     [VCC]           -->     P9 PIN 3   [VDD_3V3]
            BLUE    [EAP_TX]        -->     P9 PIN 24  [UART1_TXD]
            ORANGE  [EAP_RX]        -->     P9 PIN 26  [UART1_RXD]
            YELLOW  [EAP_RX_ACK]    -->     P8 PIN 7   [GPIO2_2]

    - optionally connect an external LED driver using jumper wires:

            Ground                  -->     P8 PIN 1   [DGND]
            LED signal (3v3)        -->     P8 PIN 10  [GPIO2_4]

TOOLING ENVIRONMENT

    - GNU make, binutils, gcc (pre-installed on BeagleBone Black)
    - Java development kit: http://beagleboard.org/project/java
    - Emmoco em-builder command line tool:
          opkg install emmoco-tools-linux-all-*.deb
    
NOTES

    - developed against unmodified Angstrom Linux (3.8.13 kernel)
    - copy the examples-lp/ file hierarchy to the BeagleBone Black SBC
    - build and execute on BeagleBone Black as root user:
    
         cd examples-lp/Blinker-EmbeddedLinux/
         make
         ./Output/Blinker-Prog.out

LINKS

    - http://www.beagleboard.org/black

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

    sysFd = open("/sys/devices/bone_capemgr.9/slots", O_WRONLY);
    if (sysFd < 0) {
            perror("open SLOTS");
            exit(-1);
    }
    write(sysFd, "BB-UART1", 8); // enable UART1
    close(sysFd);

    sysFd = open("/sys/class/gpio/export", O_WRONLY);
    if (sysFd < 0) {
        perror("open GPIO export");
        exit(-1);
    }
    write(sysFd, "66", 2); // export GPIO2_2 to user space
    close(sysFd);

    sysFd = open("/sys/class/gpio/gpio66/direction", O_WRONLY);
    if (sysFd < 0) {
        perror("open GPIO2_2 direction");
        exit(-1);
    }
    write(sysFd, "out", 3); // use GPIO2_2 for EAP_RX_ACK output
    close(sysFd);

    sysFd = open("/sys/class/gpio/export", O_WRONLY);
    if (sysFd < 0) {
        perror("open GPIO export");
        exit(-1);
    }
    write(sysFd, "67", 2); // export GPIO2_3 to user space
    close(sysFd);

    sysFd = open("/sys/class/gpio/gpio67/direction", O_WRONLY);
    if (sysFd < 0) {
        perror("open GPIO2_3 direction");
        exit(-1);
    }
    write(sysFd, "in", 2); // use GPIO2_3 for EAP_TX_ACK input
    close(sysFd);

    sysFd = open("/sys/class/gpio/gpio67/edge", O_WRONLY);
    if (sysFd < 0) {
        perror("open GPIO2_3 edge");
        exit(-1);
    }
    write(sysFd, "falling", 7); // configure GPIO2_3 for EAP_TX_ACK interrupt
    close(sysFd);

    sysFd = open("/sys/class/gpio/export", O_WRONLY);
    if (sysFd < 0) {
       perror("open GPIO export");
       exit(-1);
    }
    write(sysFd, "68", 2); // export GPIO2_4 to user space
    close(sysFd);

    sysFd = open("/sys/class/gpio/gpio68/direction", O_WRONLY);
    if (sysFd < 0) {
        perror("open GPIO2_4 direction");
        exit(-1);
    }
    write(sysFd, "out", 3); // use GPIO2_4 for LED output
    close(sysFd);

    rxAckFd = open("/sys/class/gpio/gpio66/value", O_WRONLY); // open EAP_RX_ACK output
    if (rxAckFd < 0) {
        perror("open GPIO2_2");
        exit(-1);
    }

    txAckFd = open("/sys/class/gpio/gpio67/value", O_RDONLY); // open EAP_TX_ACK input
    if (txAckFd < 0) {
        perror("open GPIO2_3");
        exit(-1);
    }

    ledFd = open("/sys/class/gpio/gpio68/value", O_WRONLY); // open LED output
    if (ledFd < 0) {
        perror("open GPIO2_4");
        exit(-1);
    }

    uartFd = open("/dev/ttyO1", O_RDWR | O_NOCTTY | O_NONBLOCK); // open serial UART1
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
