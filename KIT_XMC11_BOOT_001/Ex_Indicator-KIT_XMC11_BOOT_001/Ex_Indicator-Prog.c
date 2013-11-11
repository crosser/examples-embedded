#include "Ex_Indicator.h"
#include "Hal.h"

static void buttonHandler(void);

Ex_Indicator_eventSelector_t eventSelectorVal = Ex_Indicator_NONE;

void main() {
    Hal_init();
    Hal_buttonEnable(buttonHandler);
    Ex_Indicator_start();
    Hal_idleLoop();
}

static void buttonHandler(void) {
    Hal_ledOn();
    Hal_delay(500);
    Hal_ledOff();
    switch (eventSelectorVal) {
        case Ex_Indicator_VOID_EVENT:
            Ex_Indicator_eventA_indicate();
            break;
        case Ex_Indicator_UINT8_EVENT:
            Ex_Indicator_eventB_indicate();
            break;
        case Ex_Indicator_INT32_EVENT:
            Ex_Indicator_eventC_indicate();
            break;
    }
}

/* -------- SCHEMA CALLBACKS -------- */

void Ex_Indicator_connectHandler(void) {
    Hal_connected();
}

void Ex_Indicator_disconnectHandler(void) {
    Hal_disconnected();
}

void Ex_Indicator_eventSelector_fetch(Ex_Indicator_eventSelector_t* const output) {
    *output = eventSelectorVal;
}

void Ex_Indicator_eventSelector_store(Ex_Indicator_eventSelector_t* const input) {
    eventSelectorVal = *input;
}

void Ex_Indicator_eventB_fetch(Ex_Indicator_eventB_t* const output) {
    *output = 123;
}

void Ex_Indicator_eventC_fetch(Ex_Indicator_eventC_t* const output) {
    *output = 12345678;
}
