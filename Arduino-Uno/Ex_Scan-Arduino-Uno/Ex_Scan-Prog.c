#include "Ex_Scan.h"
#include "Hal.h"

static Ex_Scan_numDevices_t numDevicesVal = 0;
static Ex_Scan_devices_t devicesVal;

static void buttonHandler(void);

void main() {
	Hal_init();
    Hal_buttonEnable(buttonHandler);
	Ex_Scan_start();    
	Hal_idleLoop();
}

static void buttonHandler(void) {
    uint8_t i, j;
    Hal_ledOn();
    Hal_delay(500);
    Hal_ledOff();
    Hal_debugPulse(1);
    numDevicesVal = 0;          // Clear out the schema data before the scan
    for (i = 0; i < Ex_Scan_devices_length; i++) {
        memset(devicesVal[i].name, 0, Ex_Scan_DeviceName_length);
        devicesVal[i].rssi = 0;
    }
    Ex_Scan_scan(2000, Ex_Scan_Blinker);
}

void Ex_Scan_connectHandler(void) {
    Hal_connected();
}

void Ex_Scan_disconnectHandler(void) {
    Hal_disconnected();
}

void Ex_Scan_scanDoneHandler(uint8_t numDevices) {
    numDevicesVal = numDevices;
    Hal_debugPulse(2);
}

void Ex_Scan_devices_fetch(Ex_Scan_devices_t output) {
    uint8_t i;
    for (i = 0; i < Ex_Scan_devices_length; i++) {
        memcpy(output[i].name, devicesVal[i].name, Ex_Scan_DeviceName_length);
        output[i].rssi = devicesVal[i].rssi;
    }
}

void Ex_Scan_numDevices_fetch(Ex_Scan_numDevices_t* output) {
    *output = numDevicesVal;
}

void Blinker_scanDeviceHandler(Em_Device* device) {     // Called once for each device found on the scan
    if (numDevicesVal < Ex_Scan_devices_length) {       // Limited to the first Ex_Scan_devices_length devices found just for the demo
        memcpy (devicesVal[numDevicesVal].name, device->name, Ex_Scan_DeviceName_length-1);
        devicesVal[numDevicesVal].rssi = device->rssi;
        numDevicesVal++;
    }
    Hal_debugPulse(1);
}

void Blinker_ledState_indicator(Blinker_ledState_t data) {
}
