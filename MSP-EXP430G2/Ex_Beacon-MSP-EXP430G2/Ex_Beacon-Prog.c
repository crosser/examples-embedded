#include "Ex_Beacon.h"
#include "Hal.h"

const uint8_t UUID[] = {0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,0x88,0x99,0xAA,0xBB,0xCC,0xDD,0xEE,0xFF};
const uint16_t MAJOR = 20;
const uint16_t MINOR = 500;

static void buttonHandler(void);
static void commandDoneHandler(void);
static bool beaconEnabled = false;

void main() {
	Hal_init();
    Hal_buttonEnable(buttonHandler);
    Ex_Beacon_onCommandDone(commandDoneHandler);
    Ex_Beacon_setBeaconInfo(UUID, MAJOR, MINOR);
	Ex_Beacon_start();    
	Hal_idleLoop();
}

static void buttonHandler(void) {
    Hal_ledOn();
    Hal_delay(500);
    Hal_ledOff();
    Hal_debugPulse(1);
    if (!beaconEnabled) {
        Ex_Beacon_beacon();
    }
    else {
        Ex_Beacon_accept(true);
    }
    beaconEnabled ^= true;
}

static void commandDoneHandler(void) {
    if (beaconEnabled) {
        Hal_connected();
    }
    else {
        Hal_disconnected();
    }
}

void Ex_Beacon_connectHandler(void) {
    Hal_connected();
}

void Ex_Beacon_disconnectHandler(void) {
    Hal_disconnected();
}
