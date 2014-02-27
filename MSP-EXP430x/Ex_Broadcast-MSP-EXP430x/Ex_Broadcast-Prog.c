#include "Ex_Broadcast.h"
#include "Hal.h"

static void buttonHandler(void);
static void tickHandler(void);

Ex_Broadcast_info_t infoVal = 0;                    // Initial broadcast value
bool sendInfoFlag = true;                           // Power up broadcasting

void main() {
    Hal_init();
    Ex_Broadcast_start();
    Hal_buttonEnable(buttonHandler);
    Hal_tickStart(2000, tickHandler);               // 2 sec tick
    Hal_idleLoop();
}

/*
 * buttonHandler -- toggles between broadcasting and not broadcasting the info data when advertising.
 *               -- blinks LED to acknowledge button push
 */
static void buttonHandler(void) {
    Hal_ledOn();
    Hal_delay(500);                                 // longer blink to show button push received
    Hal_ledOff();
    sendInfoFlag = !sendInfoFlag;                   // toggle sendInfoFlag
    if (sendInfoFlag) {
        Ex_Broadcast_info_broadcast();              // broadcast the current value, if now on.
    }
    else {
        Ex_Broadcast_broadcastOff();                // otherwise, end broadcasting
    }
}

/* tickHandler -- increments info value, then broadcasts.
 *             -- short blink of light each broadcast
 */
static void tickHandler(void) {
    if (sendInfoFlag) {
        Hal_ledOn();
        Hal_delay(100);                             // short blink to show "tick" while broadcasting
        Hal_ledOff();
        infoVal++;
        Ex_Broadcast_info_broadcast();              // broadcast the new value
    }
}

/* -------- SCHEMA CALLBACKS -------- */

void Ex_Broadcast_connectHandler(void) {
    Hal_connected();
}

void Ex_Broadcast_disconnectHandler(void) {
    Hal_disconnected();
}

void Ex_Broadcast_info_fetch(Ex_Broadcast_info_t* output) {
    *output = infoVal;
}
