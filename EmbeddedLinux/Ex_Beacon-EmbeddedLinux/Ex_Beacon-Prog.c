#include "Ex_Beacon.h"
#include "Hal.h"

const uint8_t UUID[] = {0xE2,0xC5,0x6D,0xB5,0xDF,0xFB,0x48,0xD2,0xB0,0x60,0xD0,0xF5,0xA7,0x10,0x96,0xE0};
const uint16_t MAJOR = 20;
const uint16_t MINOR = 500;

static void buttonHandler(void);
static bool beaconEnabled = false;

void main() {
	Hal_init();
    Hal_buttonEnable(buttonHandler);
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

void Ex_Beacon_connectHandler(void) {
    Hal_connected();
}

void Ex_Beacon_disconnectHandler(void) {
    Hal_disconnected();
}
