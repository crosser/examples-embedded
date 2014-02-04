#include "CBlinker.h"
#include "Hal.h"

static void buttonHandler(void);

static bool connected = false;
static uint8_t curCount;
static Em_Device curDevice;

void main() {
    Hal_init();
    Hal_buttonEnable(buttonHandler);
    CBlinker_start();    
    Hal_idleLoop();
}

static void buttonHandler(void) {
    if (!connected) {
        Hal_ledOn();
        Hal_delay(500);
        Hal_ledOff();
        Hal_debugPulse(1);
        CBlinker_scan(2000, CBlinker_PBlinker);
    }
}

void CBlinker_connectHandler(void) {
    Hal_connected();
    connected = true;
}

void CBlinker_disconnectHandler(void) {
    Hal_disconnected();
    Hal_ledOff();
    curCount = 0;
    connected = false;
}

void CBlinker_scanDoneHandler(uint8_t numDevices) {
    if (numDevices > 0) {
        curCount = 6;
        PBlinker_connect(&curDevice, 10, NULL);
    }   
}

void PBlinker_scanDeviceHandler(Em_Device* device) {
    curDevice = *device;
}

void PBlinker_ledState_indicator(PBlinker_ledState_t data) {
    if (curCount == 0) {
        CBlinker_disconnect();
        return;
    }
    curCount -= 1;
    if (data == PBlinker_LED_ON) {
        Hal_ledOn();
    }
    else {
        Hal_ledOff();
    }
}
