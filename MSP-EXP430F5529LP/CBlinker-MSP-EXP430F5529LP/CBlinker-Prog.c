/**
 *  ----- CBlinker-Prog.c ----- 
 * 
 * This example program demonstrates operating as a central in conjunction with a peripheral running Blinker.
 *
 * Non-Blocking Technique Used:
 * ============================
 * It is very important to note that operation as a central node is done with a non-blocking, event-driven technique
 * using callbacks.  So an action is started, and essentially immediately returns to the idle loop.  When the action is
 * completed, a callback is issued to determine what (if any) the next action should be.
 *
 * Some of the callbacks are explicit (specified in the call to start the action).  And some of the callbacks are 
 * implicit (given by the specific action started).  For example,
 *   CBlinker_scan -- implicit callbacks to scanDeviceHandler and scanDoneHandler
 *   PBlinker_connect -- explicit success callback specified in call -- implicit failure callback to CBlinker_disconnectHandler().
 * 
 * CBlinker Example Operation:
 * ========================
 * Upon a button push, this example "scans" for a peripheral device running the Blinker schema (as specified in the schema.properties file).
 * As it scans it records the number of such devices found, and for this example, it records the descriptor of
 * the last such device found.  
 * If no such devices are found, the program goes back to the idle loop.
 * If it finds at least one such device, then it will do the following:
 *   connect to the last such device found (and remember that there is no ordering to those found).
 *   Await indicators from the Blinker device and mimic the blinking on the Blinker device for several blinks
 *   disconnect
 *   go back to idle state awaiting the next button push
 *
 * Notes:
 * Once the CBlinker program returns to the idle state awaiting a button push, it is operating as a peripheral.  As such, it can be
 * connected to (by Em-Browser for example), and the data in the CBlinker.ems schema can be examined.  For example, after each "run"
 * caused by a button push, the deviceName of the Blinker device should be present.
 *
 * CBlinker to Blinker Resource Data Transfers:
 * =========================================
 * For any resources transferred between this CBlinker device and the Blinker device connected, the data transfer goes through an I/O buffer.
 * As such, 
 *   before an over-the-air write from CBlinker to Blinker, the data to be transferred must be placed in iobuf
 *   and after an over-the-air read from Blinker into CBlinker, the data transferred must be copied out of iobuf for storage.
 */
#include "CBlinker.h"
#include "Hal.h"

#define NUM_INDICATORS_TO_MIMIC 20

// Private Method Prototypes
static void buttonHandler(void);
static void doConnect(void);
static void doDisconnect(void);
static void doScan(void);

// Schema Data -- available when CBlinker device not connected to Blinker device.
CBlinker_blinkerDeviceName_t blinkerDeviceName;                 // Name of Blinker device last connected
CBlinker_numBlinkerDevicesSeen_t numBlinkerDevicesSeen = 0;     // Number of Blinker devices seen on last scan

// Private Data
static Em_Device curDevice;                                     // Current device descriptor
static uint8_t curCount;                                        // Number of blinks left to mimic

/**
 * ----- main -----
 * Initialize device, enable button interrupt / handler, start Schema RunTime, and go into Idle loop awaiting events
 */ 
void main() {
    Hal_init();
    Hal_buttonEnable(buttonHandler);
    CBlinker_start();    
    Hal_idleLoop();
}

/* -------------------------------------------------------------------------------------------
 *                                       Private Methods  
 * -------------------------------------------------------------------------------------------
 */

/**
 * ----- buttonHandler -----
 * 
 * Issue half-second LED to acknowledge button push
 * Then, do a scan for Blinker devices.
 *
 * @param   none
 * @return  none
 */
static void buttonHandler(void) {
    Hal_ledOn();
    Hal_delay(500);
    Hal_ledOff();
    doScan();
}

/**
 * ----- doConnect -----
 * Attempts to connect to the Blinker device found.
 *
 * Callbacks:
 *   CBlinker_connectHandler() if connected
 *   CBlinker_disconnectHandler() if not.
 *
 * @param   none
 * @return  none
 */
static void doConnect(void) {
// PBlinker_connect will attempt to connect to curDevice for 10s
// Note bug EM-63:  the timeout is not yet implemented.  So it will attempt to connect forever.
    PBlinker_connect(&curDevice, 10, CBlinker_connectHandler);
}

/**
 * ----- doDisconnect -----
 * Disconnects from Blinker device.
 *
 * Callback:
 *   Implicit callback to CBlinker_disconnectHandler once complete.
 *
 * @param   none
 * @return  none
 */
static void doDisconnect(void) {
    CBlinker_disconnect();                          // Disconnect from peripheral device
}

/**
 ----- doScan -----
 * Scan for Blinker peripheral devices.
 *
 * Callbacks:
 *   scanDeviceHandler:     Once per device found.
 *   scanDoneHandler:       Upon completion of scan.
 * Notes:
 *   There may be no devices found.
 *   The order of the devices found is random.
 *
 * @param   none
 * @return  none
 */
static void doScan(void) {
    numBlinkerDevicesSeen = 0;                          // Clear device count before scan.
    blinkerDeviceName[0] = '\0';                        // Clear deviceName before scan.
    CBlinker_scan(2000, CBlinker_PBlinker);             // Scan for Blinker devices.
}

/* -------------------------------------------------------------------------------------------
 *                                  CBlinker-STUBS.c Callbacks  
 * -------------------------------------------------------------------------------------------
 */

/**
 * ----- CBlinker_connectHandler -----
 * Called by SRT whenever this CBlinker device is connected to as a peripheral.
 * Called explicitly in doRead when it connects as a central to an Blinker device.
 * Turns on the Connected LED.
 *
 * @param   none
 * @return  none
 */
void CBlinker_connectHandler(void) {
    Hal_connected();
}

/**
 * ----- CBlinker_disconnectHandler -----
 * Called whenever this CBlinker device disconnects from another device.  Plus this is called
 * whenever the MCM resets.  So there will always be a callback here upon a reset.
 * Turns off the Connected LED.
 *
 * @param   none
 * @return  none
 */
void CBlinker_disconnectHandler(void) {
    Hal_ledOff();                                   // Turn off the LED
    Hal_disconnected();
}

/**
 * ----- CBlinker_blinkerDeviceName_fetch -----
 * Called whenever a connected device requests the value of the resource.  Copies the blinkerDeviceName value to output.
 *
 * @param   output - array to store the blinkerDeviceName in.
 * @return  none
 */
void CBlinker_blinkerDeviceName_fetch(CBlinker_blinkerDeviceName_t output) {
    memcpy(output, blinkerDeviceName, sizeof(CBlinker_blinkerDeviceName_t));
}

/**
 * ----- CBlinker_numBlinkerDevicesSeen_fetch -----
 * Called whenever a connected device requests the value of the resource.  Copies the numBlinkerDevicesSeen value to output.
 *
 *
 * @param   output - pointer to buffer to store numBlinkerDevicesSeen in
 * @return  none
 */
void CBlinker_numBlinkerDevicesSeen_fetch(CBlinker_numBlinkerDevicesSeen_t* output) {
    *output = numBlinkerDevicesSeen;
}

/**
 * ----- CBlinker_scanDoneHandler -----
 * Called whenever a scan operation completes.  
 * If a device was found, copies the name of the device (if found) into blinkerDeviceName.
 * Then goes to doConnect.
 * If not, go back to the idle loop.
 *
 * Callbacks:
 *   doConnect if an Blinker device was found.
 *
 * @param   numDevices - the number of Blinker devices seen on the scan
 * @return  none
 */
void CBlinker_scanDoneHandler(uint8_t numDevices) {
    if (numDevices > 0) {
        memcpy(blinkerDeviceName, curDevice.name, CBlinker_DeviceName_length);
        curCount = NUM_INDICATORS_TO_MIMIC;                 // Set up to mimic indicators
        doConnect();
    }   
}

/* -------------------------------------------------------------------------------------------
 *                                  PBlinker-STUBS.c Callbacks  
 * -------------------------------------------------------------------------------------------
 */

/**
 * ----- PBlinker_ledState_indicator -----
 * Called whenever a the CBlinker receives an indicator from the connected Blinker device.
 * Disconnects after the count winds down.
 *
 * @param   ledState - ledState value indicated
 * @return  none
 */
void PBlinker_ledState_indicator(PBlinker_ledState_t ledState) {
    if (ledState == PBlinker_LED_ON) {      // Mimic the ledState
        Hal_ledOn();
    }
    else {
        Hal_ledOff();
    }
    if (curCount == 0) {
        doDisconnect();
    }
    else {
        curCount--;
    }
}

/**
 * ----- PBlinker_scanDeviceHandler -----
 * Called whenever a scan operation finds a Blinker device.  Copies the device descriptor into curDevice.
 * Increments the numBlinkerDevicesSeen.
 *
 * Note:  For this example, this only saves the last device found.  Others are thrown away.  This is simply
 * to minimize storage for small RAM microcontrollers.
 *
 * @param   device - pointer to device descriptor for the Blinker device found on the scan
 * @return  none
 */
void PBlinker_scanDeviceHandler(Em_Device* device) {
    numBlinkerDevicesSeen++;
    curDevice = *device;
}
