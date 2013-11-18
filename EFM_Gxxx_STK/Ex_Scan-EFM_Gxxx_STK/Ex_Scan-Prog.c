#include "Ex_Scan.h"
#include "Hal.h"

static void buttonHandler(void);

void main() {
	Hal_init();
    Hal_buttonEnable(buttonHandler);
	Ex_Scan_start();    
	Hal_idleLoop();
}

static void buttonHandler(void) {
    Hal_ledOn();
    Hal_delay(500);
    Hal_ledOff();
    Hal_debugPulse(1);
    Ex_Scan_scan(2000, Ex_Scan_Blinker);
}

void Ex_Scan_connectHandler(void) {
    Hal_connected();
}

void Ex_Scan_disconnectHandler(void) {
    Hal_disconnected();
}

void Ex_Scan_scanDoneHandler(uint8_t numDevices) {
    Hal_debugPulse(2);
}

void Blinker_connectHandler(Em_Status status) {}
void Blinker_disconnectHandler(Em_Status status) {}
void Blinker_readWriteHandler(Em_Status status) {}

void Blinker_scanDeviceHandler(Em_Device* device) {
    Hal_debugPulse(1);
}

void Blinker_ledState_indicator(Blinker_ledState_t data) {
}
