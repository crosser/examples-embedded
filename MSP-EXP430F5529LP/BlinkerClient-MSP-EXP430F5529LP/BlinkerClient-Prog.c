#include "BlinkerClient.h"
#include "Hal.h"

static void buttonHandler(void);

static bool connected = false;
static uint8_t curCount;
static Em_Device curDevice;

void main() {
	Hal_init();
    Hal_buttonEnable(buttonHandler);
	BlinkerClient_start();    
	Hal_idleLoop();
}

static void buttonHandler(void) {
    if (!connected) {
        Hal_ledOn();
        Hal_delay(500);
        Hal_ledOff();
        Hal_debugPulse(1);
        BlinkerClient_scan(2000, BlinkerClient_Peri);
    }
}

void BlinkerClient_connectHandler(void) {
    Hal_connected();
    connected = true;
}

void BlinkerClient_disconnectHandler(void) {
    Hal_disconnected();
    Hal_ledOff();
    curCount = 0;
    connected = false;
}

void BlinkerClient_scanDoneHandler(uint8_t numDevices) {
    if (numDevices > 0) {
        curCount = 6;
        Peri_connect(&curDevice, 10, NULL);
    }   
}

void Peri_scanDeviceHandler(Em_Device* device) {
    curDevice = *device;
}

void Peri_ledState_indicator(Peri_ledState_t data) {
    if (curCount == 0) {
        BlinkerClient_disconnect();
        return;
    }
    curCount -= 1;
    if (data == Peri_LED_ON) {
        Hal_ledOn();
    }
    else {
        Hal_ledOff();
    }
}
