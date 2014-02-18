/*
 * ============ Hardware Abstraction Layer for BeagleBone Black ============
 */

/*

DESCRIPTION

    - an implementation of the Emmoco HAL for the BeagleBone Black SBC
    - the board's UART1 serial port is used for communication
    - the board's GPIO2_2 and GPIO2_3 lines are used for handshaking
    - the board's GPIO2_1 line may be used to monitor connection status
    - the board's GPIO2_4 line may be used to switch an external LED
    - the board's GPIO2_5 line may be used for external button input

PLATFORM CONFIGURATION

    - configure your EDB firmware with factory default settings

    - connect your EDB to the BeagleBone Black board using your Em-Cable:

            BLACK   [GND]           -->     P9 PIN 1   [DGND]
            WHITE   [EAP_TX_ACK]    -->     P8 PIN 8   [GPIO2_3]
            RED     [VCC]           -->     P9 PIN 3   [VDD_3V3]
            BLUE    [EAP_TX]        -->     P9 PIN 24  [UART1_TXD]
            ORANGE  [EAP_RX]        -->     P9 PIN 26  [UART1_RXD]
            YELLOW  [EAP_RX_ACK]    -->     P8 PIN 7   [GPIO2_2]

    - optionally connect external peripherals using jumper wires:

            Ground                  -->     P9 PIN 2   [DGND]
            Ground                  -->     P8 PIN 1   [DGND]
            Ground                  -->     P8 PIN 2   [DGND]
            Connected signal (3v3)  -->     P8 PIN 18  [GPIO2_1]
            LED signal (3v3)        -->     P8 PIN 10  [GPIO2_4]
            Button (wire to ground) -->     P8 PIN 9   [GPIO2_5]

TOOLING ENVIRONMENT

    - GNU make, binutils, gcc (pre-installed on BeagleBone Black)
    - Java development kit: http://beagleboard.org/project/java
    - Emmoco em-builder command line tool:
          opkg install emmoco-tools-linux-all-*.deb

NOTES

    - developed against unmodified Angstrom Linux (3.8.13 kernel)
    - copy the examples-embedded/ file hierarchy to the BeagleBone Black SBC
    - build and execute on BeagleBone Black as root user:

         cd examples-embedded/EmbeddedLinux/Blinker-EmbeddedLinux/
         make
         Output/Blinker-Prog.out

LINKS

    - http://www.beagleboard.org/black

*/

#include "Hal.h"

#include <stdlib.h> // for exit()
#include <fcntl.h> // for O_WRONLY
#include <termios.h> // for tcsetattr()
#include <sys/timerfd.h> // for timerfd
#include <dirent.h> // for DIR

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
    struct dirent *de;
    const char *devices = "/sys/devices/";
    const char *capemgr = "bone_capemgr.";
    const char *slots = "/slots";
    const int capemgrlen = strlen(capemgr);
    DIR *dir = opendir(devices);
    while (de = readdir(dir)) { // locate "bone_capemgr.*"
        if (de->d_type == DT_DIR) {
            const int dirlen = strlen(de->d_name);
            if ((dirlen > capemgrlen) && (0 == memcmp(de->d_name, capemgr, capemgrlen))) {
                char path[strlen(devices) + dirlen + strlen(slots) + 1];
                memcpy(path, devices, strlen(devices) + 1);
                strcat(path, de->d_name);
                strcat(path, slots);
                sysWrite(path, "BB-UART1"); // enable UART1
                break;
            }
        }
    }
    closedir(dir);

    sysWrite("/sys/class/gpio/export", "69"); // export GPIO2_5 to user space
    sysWrite("/sys/class/gpio/gpio69/direction", "in"); // use GPIO2_5 for button input
    sysWrite("/sys/class/gpio/gpio69/edge", "falling"); // configure GPIO2_5 for button interrupt
    sysWrite("/sys/class/gpio/export", "65"); // export GPIO2_1 to user space
    sysWrite("/sys/class/gpio/gpio65/direction", "out"); // use GPIO2_1 for connected output
    sysWrite("/sys/class/gpio/export", "68"); // export GPIO2_4 to user space
    sysWrite("/sys/class/gpio/gpio68/direction", "out"); // use GPIO2_4 for LED output
    sysWrite("/sys/class/gpio/export", "66"); // export GPIO2_2 to user space
    sysWrite("/sys/class/gpio/gpio66/direction", "out"); // use GPIO2_2 for EAP_RX_ACK output
    sysWrite("/sys/class/gpio/export", "67"); // export GPIO2_3 to user space
    sysWrite("/sys/class/gpio/gpio67/direction", "in"); // use GPIO2_3 for EAP_TX_ACK input
    sysWrite("/sys/class/gpio/gpio67/edge", "falling"); // configure GPIO2_3 for EAP_TX_ACK interrupt

    buttonFd = sysOpen("/sys/class/gpio/gpio69/value", O_RDONLY); // open button input
    connectedFd = sysOpen("/sys/class/gpio/gpio65/value", O_WRONLY); // open connected output
    ledFd = sysOpen("/sys/class/gpio/gpio68/value", O_WRONLY); // open LED output
    rxAckFd = sysOpen("/sys/class/gpio/gpio66/value", O_WRONLY); // open EAP_RX_ACK output
    txAckFd = sysOpen("/sys/class/gpio/gpio67/value", O_RDONLY); // open EAP_TX_ACK input
    uartFd = sysOpen("/dev/ttyO1", O_RDWR | O_NOCTTY | O_NONBLOCK); // open serial UART1

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
