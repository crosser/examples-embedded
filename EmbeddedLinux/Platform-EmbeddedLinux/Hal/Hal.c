/*
 * ============ Hardware Abstraction Layer for Embedded Linux ============
 */

/*

DESCRIPTION

    - an implementation of the Emmoco HAL for Embedded Linux platforms
    - use in conjunction with a board-specific Hal_init() implementation
    
TOOLING ENVIRONMENT

    - GNU make, binutils, gcc
    - Java development kit
    - Emmoco em-builder command line tool
    
NOTES

    - copy the examples-lp/ file hierarchy to the embedded system
    - build and execute as root user:
    
         cd examples-lp/Blinker-EmbeddedLinux/
         make
         sudo ./Output/Blinker-Prog.out

*/

#include "Hal.h"
#include "Em_Message.h"

#include <stdlib.h> // for exit()
#include <stdio.h> // for perror()
#include <errno.h> // for EINTR
#include <sys/timerfd.h> // for timerfd

static Hal_Handler tickHandler;
static bool ledState;
int ledFd;
int uartFd;
int rxAckFd;
int txAckFd;
int timerFd;

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

void Hal_idleLoop(void) {
    int fdCount;
    int fdMax = ((txAckFd > uartFd) ? txAckFd : uartFd);
    fdMax = (timerFd > fdMax) ? timerFd : fdMax;
    fdMax++;
    fd_set exceptFdSet;
    fd_set readFdSet;
    char txAckBuf[2];
    uint8_t uartBuf;
    uint64_t timerBuf;
     
    while (1) {
        FD_ZERO(&exceptFdSet);
        FD_SET(txAckFd, &exceptFdSet);
        FD_ZERO(&readFdSet);
        FD_SET(uartFd, &readFdSet);
        FD_SET(timerFd, &readFdSet);
        fdCount = select(fdMax, &readFdSet, NULL, &exceptFdSet, NULL);
        if (fdCount == -1) {
            if (errno != EINTR) { // we expect EINTR
                printf("select() errno %d\n", errno);
                exit(-1);
            }
            continue;
        }
        if (fdCount == 0) {
            printf("select() timeout\n");
            exit(-1);
        }
        if (FD_ISSET(txAckFd, &exceptFdSet)) {
            read(txAckFd, txAckBuf, sizeof(txAckBuf)); // clear EAP_TX_ACK
            lseek(txAckFd, 0, SEEK_SET);
            if (Em_Message_getByte(&uartBuf)) {
                write(uartFd, &uartBuf, 1); // send a single byte
            }
        }
        if (FD_ISSET(uartFd, &readFdSet)) {
            if (1 != read(uartFd, &uartBuf, 1)) {
                printf("UART - nothing to read\n");
            } else {
                Em_Message_startRx();
                write(rxAckFd, "0", 1); // EAP_RX_ACK clear
                write(rxAckFd, "1", 1); // EAP_RX_ACK set
                if (Em_Message_addByte(uartBuf)) {
                    Em_Message_dispatch();
                }
            }                 
        }
        if (FD_ISSET(timerFd, &readFdSet)) {
            if (sizeof(uint64_t) == read(timerFd, &timerBuf, sizeof(uint64_t))) {
                (*tickHandler)();
            } else {
                printf("timer - nothing to read\n");
            }
        }
    }
}

void Hal_ledOn(void) {
    ledState = 1;
    write(ledFd, "1", 1);
    printf("LED on\n");
}

void Hal_ledOff(void) {
    ledState = 0;
    write(ledFd, "0", 1);
    printf("LED off\n");
}

bool Hal_ledRead(void) {
    return ledState;
}

void Hal_ledToggle(void) {
    ledState = (ledState != 1);
    write(ledFd, ledState ? "1" : "0", 1);
    printf("LED toggle\n");
}

void Hal_tickStart(uint16_t msecs, void (*handler)(void)) {
    tickHandler = handler;
    struct itimerspec spec;
    spec.it_value.tv_sec = msecs / 1000;
    spec.it_value.tv_nsec = (msecs % 1000) * 1000000;
    spec.it_interval.tv_sec = msecs / 1000;
    spec.it_interval.tv_nsec = (msecs % 1000) * 1000000;
    timerfd_settime(timerFd, 0, &spec, NULL);
    printf("tick started\n");
}

/* -------- SRT-HAL INTERFACE -------- */

uint8_t Em_Hal_lock(void) {
    return 0;
}

void Em_Hal_reset(void) {
    printf("resetting\n");
    write(rxAckFd, "0", 1); // EAP_RX_ACK clear
    usleep(100000);
    write(rxAckFd, "1", 1); // EAP_RX_ACK set
    usleep(500000);
    write(rxAckFd, "0", 1); // EAP_RX_ACK clear
    usleep(100000);
    write(rxAckFd, "1", 1); // EAP_RX_ACK set
    printf("reset done\n");
}

void Em_Hal_startSend(void) {
    char txAckBuf[2];
    read(txAckFd, txAckBuf, sizeof(txAckBuf)); // clear EAP_TX_ACK
    lseek(txAckFd, 0, SEEK_SET);
    uint8_t uartBuf = Em_Message_startTx();
    write(uartFd, &uartBuf, 1); // send the initial byte
}

void Em_Hal_unlock(uint8_t key) {
}

void Em_Hal_watchOn(void) {
}

void Em_Hal_watchOff(void) {
}
