#include "Ex_Config.h"
#include "Hal.h"

static void buttonHandler(void);

uint8_t groupId = 0;

void main() {
    Hal_init();
    Hal_buttonEnable(buttonHandler);
    Ex_Config_start();
    Hal_idleLoop();
}

static void buttonHandler(void) {
    Hal_ledOn();
    Hal_delay(500);
    Hal_ledOff();
    groupId ^= 1;
    Ex_Config_activateParameters(groupId);
}

/* -------- SCHEMA CALLBACKS -------- */

void Ex_Config_connectHandler(void) {
    Hal_connected();
}

void Ex_Config_disconnectHandler(void) {
    Hal_disconnected();
}
