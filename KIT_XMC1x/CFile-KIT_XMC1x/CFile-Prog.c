#include "CFile.h"
#include "Hal.h"

static void buttonHandler(void);
static void doDisconnect(void);
static void doRead(void);
static void doWrite(void);
static uint16_t fetchFileData(uint8_t* iobuf, int32_t offset, uint16_t count);
static uint16_t storeFileData(uint8_t* iobuf, int32_t offset, uint16_t count);

Em_Device curDevice;
int32_t curFileSize;

void main() {
    Hal_init();
    Hal_buttonEnable(buttonHandler);
    CFile_start();    
    Hal_idleLoop();
}

static void buttonHandler(void) {
    Hal_ledOn();
    Hal_delay(500);
    Hal_ledOff();
    CFile_scan(500, CFile_PFile);
}

static void doConnect(void) {
    PFile_connect(&curDevice, 10, doRead);
}

static void doRead(void) {
    curFileSize = 0;
    PFile_fileData_read(storeFileData, doWrite);
}

static uint16_t storeFileData(uint8_t* iobuf, int32_t offset, uint16_t count) {
    curFileSize += count;
    return count;
} 

static void doWrite(void) {
    PFile_fileData_write(fetchFileData, doDisconnect);
}

static uint16_t fetchFileData(uint8_t* iobuf, int32_t offset, uint16_t count) {
    int32_t rem = curFileSize - offset;
    if (rem < count) {      // signal end-of-file
        count = (uint16_t)rem;
    }
    for (uint16_t i = 0; i < count; i++) {
        iobuf[i] = (offset + i) & 0xFF;
    }
    return count;
} 

static void doDisconnect(void) {
    CFile_disconnect();
}

void CFile_connectHandler(void) {
    Hal_connected();
}

void CFile_disconnectHandler(void) {
    Hal_disconnected();
}

void CFile_scanDoneHandler(uint8_t numDevices) {
    if (numDevices > 0) {
        doConnect();
    }   
}

void PFile_scanDeviceHandler(Em_Device* device) {
    curDevice = *device;
}
