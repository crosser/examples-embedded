#include "Ex_Beacon.h"
#include "Hal.h"

const uint8_t UUID[] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF};
const int8_t POWER = -50;

static void buttonHandler(void);
static void commandDoneHandler(void);

static bool beaconEnabled = false;
static Ex_Beacon_info_t infoVal = {20, 500};
static bool restartFlag = false;

void main() {
	Hal_init();
    Hal_buttonEnable(buttonHandler);
    Ex_Beacon_onCommandDone(commandDoneHandler);
    Ex_Beacon_setBeaconInfo(UUID, infoVal.majorId, infoVal.minorId, POWER);
	Ex_Beacon_start();    
	Hal_idleLoop();
}

static void buttonHandler(void) {
    Hal_ledOn();
    Hal_delay(500);
    Hal_ledOff();
    Hal_debugPulse(1);
    if (!beaconEnabled) {
        Ex_Beacon_beacon(0);
    }
    else {
        Ex_Beacon_accept(true);
    }
    beaconEnabled ^= true;
}

static void commandDoneHandler(void) {
    if (beaconEnabled) {
        Hal_ledOn();
    }
    else {
        Hal_ledOff();
    }
}

void Ex_Beacon_connectHandler(void) {
    Hal_connected();
}

void Ex_Beacon_disconnectHandler(void) {
    Hal_disconnected();
    if (restartFlag) {
        restartFlag = false;        
        Ex_Beacon_setBeaconInfo(UUID, infoVal.majorId, infoVal.minorId, POWER);
        Ex_Beacon_reset();
        Ex_Beacon_start();
    }
    else if (beaconEnabled) {
        Ex_Beacon_beacon(0);
    }
}

void Ex_Beacon_info_fetch(Ex_Beacon_info_t* output) {
    *output = infoVal;
}

void Ex_Beacon_info_store(Ex_Beacon_info_t* input) {
    infoVal = *input;
    restartFlag = true;
}
