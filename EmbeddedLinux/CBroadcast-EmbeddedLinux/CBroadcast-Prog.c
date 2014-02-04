#include "CBroadcast.h"
#include "Hal.h"

static void blinkLed(uint8_t);
static void buttonHandler(void);

void main() {
    Hal_init();
    Hal_buttonEnable(buttonHandler);
    CBroadcast_start();    
    Hal_idleLoop();
}

static void blinkLed(uint8_t count) {
    uint8_t i;
    Hal_ledOff();
    for (i = 0; i < (count*2); i++) {
        Hal_ledToggle();
        Hal_delay(50);
    }
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
    blinkLed(4);
}

void PBroadcast_scanDeviceHandler(Em_Device* device, PBroadcast_info_t* input) {
    Hal_debugPulse(input == NULL ? 1 : 2);
    blinkLed(input == NULL ? 1 : 2);    // Blink out the input state:  1=not bcasting, 2=bcasting
    Hal_delay(500);                     // Pause between Blink outs
}
