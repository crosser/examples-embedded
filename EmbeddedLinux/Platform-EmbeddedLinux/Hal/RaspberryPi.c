/*
 * ============ Hardware Abstraction Layer for Raspberry Pi ============
 */

/*

DESCRIPTION

    - an implementation of the Emmoco HAL for the Raspberry Pi SBC
    - the board's UART 0 serial port is used for communication
    - the board's GPIO 23 and GPIO 24 lines are used for handshaking
    - the board's GPIO 17 line may be used to monitor connection status
    - the board's GPIO 22 line may be used to switch an external LED
    - the board's GPIO 3 line may be used for external button input

PLATFORM CONFIGURATION

    - configure your EDB firmware with factory default settings

    - connect your EDB to the Raspberry Pi board using your Em-Cable:
      
            BLACK   [GND]           -->     P1 PIN 6   [GND]
            WHITE   [EAP_TX_ACK]    -->     P1 PIN 18  [GPIO 24]
            RED     [VCC]           -->     P1 PIN 17  [3v3 Power]
            BLUE    [EAP_TX]        -->     P1 PIN 8   [TXD]
            ORANGE  [EAP_RX]        -->     P1 PIN 10  [RXD]
            YELLOW  [EAP_RX_ACK]    -->     P1 PIN 16  [GPIO 23]

    - optionally connect external peripherals using jumper wires:

            Ground                  -->     P1 PIN 9   [GND]
            Ground                  -->     P1 PIN 14  [GND]
            Ground                  -->     P1 PIN 20  [GND]
            Connected signal (3v3)  -->     P1 PIN 11  [GPIO 17]
            LED signal (3v3)        -->     P1 PIN 15  [GPIO 22]
            Button (wire to ground) -->     P1 PIN 5   [GPIO 3]

TOOLING ENVIRONMENT

    - GNU make, binutils, gcc (pre-installed on Raspberry Pi)
    - Java development kit:
          sudo apt-get install oracle-java7-jdk
    - Emmoco em-builder command line tool:
          sudo dpkg -i emmoco-tools-linux-all-*.deb

NOTES

    - developed against unmodified Raspbian Linux (3.6.11+ kernel)
    - copy the examples-embedded/ file hierarchy to the Raspberry Pi SBC
    - disable the serial console on UART 0 by commenting out the
      following line in /etc/inittab as root user (then reboot):

         T0:23:respawn:/sbin/getty -L ttyAMA0 115200 vt100

    - build and execute on Raspberry Pi as root user:

         cd examples-embedded/EmbeddedLinux/Blinker-EmbeddedLinux/
         make
         sudo Output/Blinker-Prog.out

LINKS

    - http://www.raspberrypi.org

*/

#include "Hal.h"

#include <stdlib.h> // for exit()
#include <fcntl.h> // for O_WRONLY
#include <termios.h> // for tcsetattr()
#include <sys/timerfd.h> // for timerfd

extern int ledFd;
extern int uartFd;
extern int rxAckFd;
extern int txAckFd;
extern int timerFd;
extern int buttonFd;
extern int connectedFd;

static int sysOpen(const char *device, int flags) {
    int fd = open(device, flags);
    if (fd < 0) {
        perror(device);
        exit(EXIT_FAILURE);
    }
    return fd;
}

static void sysWrite(const char *device, const char *buffer) {
    int fd = open(device, O_WRONLY);
    if (fd < 0) {
        perror(device);
        exit(EXIT_FAILURE);
    }
    write(fd, buffer, strlen(buffer));
    close(fd);
}

/* -------- APP-HAL INTERFACE -------- */

void Hal_init() {
    sysWrite("/sys/class/gpio/export", "3"); // export GPIO 3 to user space (use GPIO 1 on rev 1 boards)
    sysWrite("/sys/class/gpio/gpio3/direction", "in"); // use GPIO 3 for button input
    sysWrite("/sys/class/gpio/gpio3/edge", "falling"); // configure GPIO 3 for button interrupt
    sysWrite("/sys/class/gpio/export", "17"); // export GPIO 17 to user space
    sysWrite("/sys/class/gpio/gpio17/direction", "out"); // use GPIO 17 for connected output
    sysWrite("/sys/class/gpio/export", "22"); // export GPIO 22 to user space
    sysWrite("/sys/class/gpio/gpio22/direction", "out"); // use GPIO 22 for LED output
    sysWrite("/sys/class/gpio/export", "23"); // export GPIO 23 to user space
    sysWrite("/sys/class/gpio/gpio23/direction", "out"); // use GPIO 23 for EAP_RX_ACK output
    sysWrite("/sys/class/gpio/export", "24"); // export GPIO 24 to user space
    sysWrite("/sys/class/gpio/gpio24/direction", "in"); // use GPIO 24 for EAP_TX_ACK input
    sysWrite("/sys/class/gpio/gpio24/edge", "falling"); // configure GPIO 24 for EAP_TX_ACK interrupt

    buttonFd = sysOpen("/sys/class/gpio/gpio3/value", O_RDONLY); // open button input
    connectedFd = sysOpen("/sys/class/gpio/gpio17/value", O_WRONLY); // open connected output
    ledFd = sysOpen("/sys/class/gpio/gpio22/value", O_WRONLY); // open LED output
    rxAckFd = sysOpen("/sys/class/gpio/gpio23/value", O_WRONLY); // open EAP_RX_ACK output
    txAckFd = sysOpen("/sys/class/gpio/gpio24/value", O_RDONLY); // open EAP_TX_ACK input
    uartFd = sysOpen("/dev/ttyAMA0", O_RDWR | O_NOCTTY | O_NONBLOCK); // open serial UART 0

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
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }

    timerFd = timerfd_create(CLOCK_REALTIME, TFD_NONBLOCK); // create HAL tick timer
    if (timerFd < 0) {
        perror("timerfd_create");
        exit(EXIT_FAILURE);
    }

    printf("initialized\n");
}
