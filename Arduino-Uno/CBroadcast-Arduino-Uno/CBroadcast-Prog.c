/**
 *  ----- CBroadcast-Prog.c ----- 
 * 
 * This example program demonstrates operating as a central in conjunction with a peripheral running Ex_Broadcast.
 *
 * Non-Blocking Technique Used:
 * ============================
 * It is very important to note that operation as a central node is done with a non-blocking, event-driven technique
 * using callbacks.  So an action is started, and essentially immediately returns to the idle loop.  When the action is
 * completed, a callback is issued to determine what (if any) the next action should be.
 *
 * Some of the callbacks are explicit (specified in the call to start the action).  And some of the callbacks are 
 * implicit (given by the specific action started).  For example,
 *   CBroadcast_scan -- implicit callbacks to scanDeviceHandler and scanDoneHandler
 *   PBroadcast_connect -- explicit success callback specified in call -- implicit failure callback to CBroadcast_disconnectHandler().
 * 
 * CBroadcast Example Operation:
 * =============================
 * Upon a button push, this example "scans" for a peripheral device running the Ex_Broadcast schema (as specified in the schema.properties file).
 * As it scans it records the number of such devices found, and for this example, it records the name and broadcast value
 * of the first few such devices found (as specified by the size of the array in CBroadcast.ems).  
 *
 * Notes:
 * Once the CBroadcast program returns to the idle state awaiting a button push, it is operating as a peripheral.  As such, it can be
 * connected to (by Em-Browser for example), and the data in the CBroadcast.ems schema can be examined.  For example, the deviceNames
 * and broadcast values (0 if broadcast off) of the first few Ex_Broadcast devices should be present.
 */
#include "CBroadcast.h"
#include "Hal.h"

// Private Method Prototypes
static void blinkLed(uint8_t);
static void buttonHandler(void);
static void doScan(void);

// Schema Data -- available when CBroadcast device not connected to Ex_Broadcast device.
CBroadcast_ex_broadcastDevices_t ex_broadcastDevices;                       // Name / info for the first few devices seen
CBroadcast_numEx_BroadcastDevicesSaved_t numEx_BroadcastDevicesSaved = 0;   // Number saved in ex_broadcastDevices
CBroadcast_numEx_BroadcastDevicesSeen_t numEx_BroadcastDevicesSeen = 0;     // Total number of Ex_Broadcast devices seen on last scan
/**
 * ----- main -----
 * Initialize device, enable button interrupt / handler, start Schema RunTime, and go into Idle loop awaiting events
 */ 
void main() {
    Hal_init();
    Hal_buttonEnable(buttonHandler);
    CBroadcast_start();    
    Hal_idleLoop();
}

/* -------------------------------------------------------------------------------------------
 *                                       Private Methods  
 * -------------------------------------------------------------------------------------------
 */

/**
 * ----- blinkLed -----
 * 
 * Blinks the LED count times
 *
 * @param   count - number of blinks
 * @return  none
 */
static void blinkLed(uint8_t count) {
    uint8_t i;
    Hal_ledOff();
    for (i = 0; i < count; i++) {
        Hal_ledToggle();
        Hal_delay(50);
        Hal_ledToggle();
        Hal_delay(150);
    }
}

/**
 * ----- buttonHandler -----
 * 
 * Issue half-second LED to acknowledge button push
 * Then, do a scan for Ex_Broadcast devices.
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
 ----- doScan -----
 * Scan for Ex_Broadcast peripheral devices.
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
    uint8_t i;
    numEx_BroadcastDevicesSeen = 0;                         // Clear device count before scan.
    numEx_BroadcastDevicesSaved = 0;
    for (i = 0; i < CBroadcast_ex_broadcastDevices_length; i++) {
        ex_broadcastDevices[i].name[0] = '\0';              // Clear the devices out too.
        ex_broadcastDevices[i].broadcastOn = 0;
        ex_broadcastDevices[i].info = 0;
    }
    CBroadcast_scan(2000, CBroadcast_PBroadcast);           // Scan for Ex_Broadcast devices.
}

/* -------------------------------------------------------------------------------------------
 *                                  CBroadcast-STUBS.c Callbacks  
 * -------------------------------------------------------------------------------------------
 */

/**
 * ----- CBroadcast_connectHandler -----
 * Called by SRT whenever this CBroadcast device is connected to as a peripheral.
 * Called explicitly in doRead when it connects as a central to an Ex_Broadcast device.
 * Turns on the Connected LED.
 *
 * @param   none
 * @return  none
 */
void CBroadcast_connectHandler(void) {
    Hal_connected();
}

/**
 * ----- CBroadcast_disconnectHandler -----
 * Called whenever this CBroadcast device disconnects from another device.  Plus this is called
 * whenever the MCM resets.  So there will always be a callback here upon a reset.
 * Turns off the Connected LED.
 *
 * @param   none
 * @return  none
 */
void CBroadcast_disconnectHandler(void) {
    Hal_disconnected();
}

/**
 * ----- CBroadcast_ex_broadcastDevices_fetch -----
 * Called whenever a connected device requests the value of the resource.  Copies the ex_broadcastDevices array to output.
 *
 *
 * @param   output - pointer to buffer to store ex_broadcastDevices array in
 * @return  none
 */
void CBroadcast_ex_broadcastDevices_fetch(CBroadcast_ex_broadcastDevices_t output) {
    memcpy(output, ex_broadcastDevices, sizeof(CBroadcast_ex_broadcastDevices_t));
}

/**
 * ----- CBroadcast_numEx_BroadcastDevicesSaved_fetch -----
 * Called whenever a connected device requests the value of the resource.  Copies the numEx_BroadcastDevicesSaved value to output.
 *
 *
 * @param   output - pointer to buffer to store numEx_BroadcastDevicesSaved in
 * @return  none
 */
void CBroadcast_numEx_BroadcastDevicesSaved_fetch(CBroadcast_numEx_BroadcastDevicesSaved_t* output) {
    *output = numEx_BroadcastDevicesSaved;
}

/**
 * ----- CBroadcast_numEx_BroadcastDevicesSeen_fetch -----
 * Called whenever a connected device requests the value of the resource.  Copies the numEx_BroadcastDevicesSeen value to output.
 *
 *
 * @param   output - pointer to buffer to store numEx_BroadcastDevicesSeen in
 * @return  none
 */
void CBroadcast_numEx_BroadcastDevicesSeen_fetch(CBroadcast_numEx_BroadcastDevicesSeen_t* output) {
    *output = numEx_BroadcastDevicesSeen;
}

/**
 * ----- CBroadcast_scanDoneHandler -----
 * Called whenever a scan operation completes.  Blinks LED 4 times  
 *
 * @param   numDevices - the number of Ex_Broadcast devices seen on the scan
 * @return  none
 */
void CBroadcast_scanDoneHandler(uint8_t numDevices) {
    blinkLed(4);            // blink LED four times to indicate end of scan
}

/* -------------------------------------------------------------------------------------------
 *                                  PBroadcast-STUBS.c Callbacks  
 * -------------------------------------------------------------------------------------------
 */

/**
 * ----- PBroadcast_scanDeviceHandler -----
 * Called whenever a scan operation finds a Ex_Broadcast device.  Saves the name and broadcast value.
 * Increments the numEx_BroadcastDevicesSeen.
 * Blinks the LED once if the device found has broadcast off.
 * Blinks the LED twice if the device is broadcasting a value.
 *
 * Note:  For this example, this only saves the first few devices found.  Others are thrown away.  This is simply
 * to minimize storage for small RAM microcontrollers.
 *
 * @param   device - pointer to device descriptor for the Ex_Broadcast device found on the scan
 * @param   input - pointer to the broadcast value.  null if broadcast is off.
 * @return  none
 */
void PBroadcast_scanDeviceHandler(Em_Device* device, PBroadcast_info_t* input) {
    numEx_BroadcastDevicesSeen++;                                               // bump the total number counter
    if (numEx_BroadcastDevicesSaved < CBroadcast_ex_broadcastDevices_length) {  // Save this one if there's room
        memcpy(ex_broadcastDevices[numEx_BroadcastDevicesSaved].name, device->name, CBroadcast_DeviceName_length);
        ex_broadcastDevices[numEx_BroadcastDevicesSaved].broadcastOn = (input != NULL ? 1 : 0); 
        ex_broadcastDevices[numEx_BroadcastDevicesSaved].info = (input != NULL ? *input : 0); 
        numEx_BroadcastDevicesSaved++;
    }
    blinkLed(input == NULL ? 1 : 2);                                            // Blink out the input state:  1=not bcasting, 2=bcasting
    Hal_delay(500);                                                             // Pause between Blink outs
}
