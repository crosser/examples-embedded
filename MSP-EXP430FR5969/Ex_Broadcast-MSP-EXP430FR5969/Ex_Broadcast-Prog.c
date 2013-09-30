#include "Ex_Broadcast.h"
#include "Hal.h"

static void buttonHandler(void);
static void tickHandler(void);

Ex_Broadcast_Data aVal = Ex_Broadcast_Data_min;     // aVal counts up from min to max
Ex_Broadcast_Data bVal = Ex_Broadcast_Data_max;     // bVal counts down from max to min
bool sendInfoFlag = false;

void main() {
    Hal_init();
    Hal_buttonEnable(buttonHandler);
    Hal_tickStart(2000, tickHandler);
    Ex_Broadcast_start();
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
    if (sendInfoFlag ^= true) {                     // toggle broadcasting
        Ex_Broadcast_info_broadcast();              // broadcast the current value, if now on.
    }
    else {
        Ex_Broadcast_broadcastOff();                // otherwise, end broadcasting
    }
}

/* tickHandler -- increments/decrements aVal/bVal, then broadcasts.
 *             -- short blink of light each broadcast
 */
static void tickHandler(void) {
    if (sendInfoFlag) {
        Hal_ledOn();
        Hal_delay(100);                             // short blink to show "tick" while broadcasting
        Hal_ledOff();
        aVal += Ex_Broadcast_Data_step;             // Go to next values
        bVal -= Ex_Broadcast_Data_step;
        if (aVal > Ex_Broadcast_Data_max) {
            aVal = Ex_Broadcast_Data_min;           // Reset on overflow/undeflow of the range
            bVal = Ex_Broadcast_Data_max;
        }
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
    Ex_Broadcast_Info_c_set(output, aVal & 0x1 ? Ex_Broadcast_C1 : Ex_Broadcast_C2);
    Ex_Broadcast_Info_d_set(output, 0, Ex_Broadcast_Data_pack(aVal));
    Ex_Broadcast_Info_d_set(output, 1, Ex_Broadcast_Data_pack(bVal));
}
