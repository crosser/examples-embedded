#include "FirstAppClient.h"
#include "Hal.h"

static void buttonHandler(void);
static void doDisconnect(void);
static void doRead(void);
static void doWrite(void);

Em_Device curDevice;

void main() {
	Hal_init();
    Hal_buttonEnable(buttonHandler);
	FirstAppClient_start();    
	Hal_idleLoop();
}

static void buttonHandler(void) {
    Hal_ledOn();
    Hal_delay(500);
    Hal_ledOff();
    FirstAppClient_scan(500, FirstAppClient_Peri);
}

static void doConnect(void) {
    Peri_connect(&curDevice, 10, doRead);
}

static void doRead(void) {
    Peri_data_read(doWrite);
}

static void doWrite(void) {
    Peri_data_t dataVal = *Peri_data_iobuf();
    dataVal += 1;
    *Peri_data_iobuf() = dataVal;
    Peri_data_write(doDisconnect);
}

static void doDisconnect(void) {
    FirstAppClient_disconnect();
}

void FirstAppClient_connectHandler(void) {
    Hal_connected();
}

void FirstAppClient_disconnectHandler(void) {
    Hal_disconnected();
}

void FirstAppClient_scanDoneHandler(uint8_t numDevices) {
    if (numDevices > 0) {
        doConnect();
    }   
}

void Peri_scanDeviceHandler(Em_Device* device) {
    curDevice = *device;
}
