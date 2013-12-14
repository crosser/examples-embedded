#include "Ex_Supervisor.h"
#include "Hal.h"

static void buttonHandler(void);

Ex_Supervisor_fxn_t fxnVal = Ex_Supervisor_NONE;
bool flag = false;

void main() {
    Hal_init();
    Hal_buttonEnable(buttonHandler);
    Ex_Supervisor_start();
    Hal_idleLoop();
}

static void buttonHandler(void) {
    Hal_ledOn();
    Hal_delay(500);
    Hal_ledOff();
    switch (fxnVal) {
        case Ex_Supervisor_DISCONNECT:
            Ex_Supervisor_disconnect();
            break;
        case Ex_Supervisor_RESTART:
            Ex_Supervisor_reset();
            Ex_Supervisor_start();
            break;
        case Ex_Supervisor_ACCEPT:
            Ex_Supervisor_accept(flag);
            flag ^= 1;
            break;
    }
}

/* -------- SCHEMA CALLBACKS -------- */

void Ex_Supervisor_connectHandler(void) {
    Hal_connected();
}

void Ex_Supervisor_disconnectHandler(void) {
    Hal_disconnected();
}

void Ex_Supervisor_fxn_fetch(Ex_Supervisor_fxn_t* const output) {
    *output = fxnVal;
}

void Ex_Supervisor_fxn_store(Ex_Supervisor_fxn_t* const input) {
    fxnVal = *input;
    flag = false;
}
