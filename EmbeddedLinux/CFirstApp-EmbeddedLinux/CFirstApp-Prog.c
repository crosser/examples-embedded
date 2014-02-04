#include "CFirstApp.h"
#include "Hal.h"

static void buttonHandler(void);
static void doDisconnect(void);
static void doRead(void);
static void doWrite(void);

Em_Device curDevice;

void main() {
    Hal_init();
    Hal_buttonEnable(buttonHandler);
    CFirstApp_start();    
    Hal_idleLoop();
}

static void buttonHandler(void) {
    Hal_ledOn();
    Hal_delay(500);
    Hal_ledOff();
    CFirstApp_scan(500, CFirstApp_PFirstApp);
}

static void doConnect(void) {
    PFirstApp_connect(&curDevice, 10, doRead);
}

static void doRead(void) {
    PFirstApp_data_read(doWrite);
}

static void doWrite(void) {
    PFirstApp_data_t dataVal = *PFirstApp_data_iobuf();
    dataVal += 1;
    *PFirstApp_data_iobuf() = dataVal;
    PFirstApp_data_write(doDisconnect);
}

static void doDisconnect(void) {
    CFirstApp_disconnect();
}

void CFirstApp_connectHandler(void) {
    Hal_connected();
}

void CFirstApp_disconnectHandler(void) {
    Hal_disconnected();
}

void CFirstApp_scanDoneHandler(uint8_t numDevices) {
    if (numDevices > 0) {
        doConnect();
    }   
}

void PFirstApp_scanDeviceHandler(Em_Device* device) {
    curDevice = *device;
}
