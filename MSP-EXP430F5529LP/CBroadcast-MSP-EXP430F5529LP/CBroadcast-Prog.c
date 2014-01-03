#include "CBroadcast.h"
#include "Hal.h"

static void buttonHandler(void);

void main() {
    Hal_init();
    Hal_buttonEnable(buttonHandler);
    CBroadcast_start();    
    Hal_idleLoop();
}

static void buttonHandler(void) {
    Hal_ledOn();
    Hal_delay(500);
    Hal_ledOff();
    CBroadcast_scan(2000, CBroadcast_PBroadcast);
}

void CBroadcast_connectHandler(void) {
    Hal_connected();
}

void CBroadcast_disconnectHandler(void) {
    Hal_disconnected();
}

void CBroadcast_scanDoneHandler(uint8_t numDevices) {
    Hal_ledOn();
}

void PBroadcast_scanDeviceHandler(Em_Device* device, PBroadcast_info_t* input) {
    Hal_debugPulse(input == NULL ? 1 : 2);
}
