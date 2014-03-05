/**
 *  ----- CFirstApp-Prog.c ----- 
 * 
 * This example program demonstrates operating as a central in conjunction with a peripheral running FirstApp.
 *
 * Non-Blocking Technique Used:
 * ============================
 * It is very important to note that operation as a central node is done with a non-blocking, event-driven technique
 * using callbacks.  So an action is started, and essentially immediately returns to the idle loop.  When the action is
 * completed, a callback is issued to determine what (if any) the next action should be.
 *
 * Some of the callbacks are explicit (specified in the call to start the action).  And some of the callbacks are 
 * implicit (given by the specific action started).  For example,
 *   CFirstApp_scan -- implicit callbacks to scanDeviceHandler and scanDoneHandler
 *   PFirstApp_connect -- explicit success callback specified in call -- implicit failure callback to CFirstApp_disconnectHandler().
 * 
 * CFirstApp Example Operation:
 * ========================
 * Upon a button push, this example "scans" for a peripheral device running the FirstApp schema (as specified in the schema.properties file).
 * As it scans it records the number of such devices found, and for this example, it records the descriptor of
 * the last such device found.  
 * If no such devices are found, the program goes back to the idle loop.
 * If it finds at least one such device, then it will do the following:
 *   connect to the last such device found (and remember that there is no ordering to those found).
 *   read the data resource from the device found
 *   increment the data read
 *   write it back to the device found
 *   read the data from the device found again to see that the incremented data was written properly
 *   go back to idle state awaiting the next button push
 *
 * Notes:
 * Once the CFirstApp program returns to the idle state awaiting a button push, it is operating as a peripheral.  As such, it can be
 * connected to (by Em-Browser for example), and the data in the CFirstApp.ems schema can be examined.  For example, after each "run"
 * caused by a button push, the data value should increment by one.  And the deviceName of the FirstApp device should be present.
 *
 * CFirstApp to FirstApp Resource Data Transfers:
 * =========================================
 * For any resources transferred between this CFirstApp device and the FirstApp device connected, the data transfer goes through an I/O buffer.
 * As such, 
 *   before an over-the-air write from CFirstApp to FirstApp, the data to be transferred must be placed in iobuf
 *   and after an over-the-air read from FirstApp into CFirstApp, the data transferred must be copied out of iobuf for storage.
 */
#include "CFirstApp.h"
#include "Hal.h"

// Private Method Prototypes
static void buttonHandler(void);
static void doDisconnect(void);
static void doRead(void);
static void doScan(void);
static void doWrite(void);
static void incrementData(void);

// Schema Data -- available when CFirstApp device not connected to FirstApp device.
CFirstApp_firstAppDeviceName_t firstAppDeviceName;              // Name of FirstApp device last connected
CFirstApp_numFirstAppDevicesSeen_t numFirstAppDevicesSeen = 0;  // Number of FirstApp devices seen on last scan
CFirstApp_data_t data;                                          // data resource value 

// Private Data
Em_Device curDevice;                                            // Current device descriptor
bool firstRead = true;                                          // Is this the first read or the last read

/**
 * ----- main -----
 * Initialize device, enable button interrupt / handler, start Schema RunTime, and go into Idle loop awaiting events
 */ 
void main() {
    Hal_init();
    Hal_buttonEnable(buttonHandler);
    CFirstApp_start();    
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
 * Then, do a scan for FirstApp devices.
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
 * Attempts to connect to the FirstApp device found.
 *
 * Callbacks:
 *   doRead if connected
 *   CFirstApp_disconnectHandler() if not.
 *
 * @param   none
 * @return  none
 */
static void doConnect(void) {
// PFirstApp_connect will attempt to connect to curDevice for 10s
// Note bug EM-63:  the timeout is not yet implemented.  So it will attempt to connect forever.
    firstRead = true;
    PFirstApp_connect(&curDevice, 10, doRead);
}

/**
 * ----- doDisconnect -----
 * Disconnects from FirstApp device.
 *
 * Callback:
 *   Implicit callback to CFirstApp_disconnectHandler once complete.
 *
 * @param   none
 * @return  none
 */
static void doDisconnect(void) {
    CFirstApp_disconnect();                             // Disconnect from peripheral device
}

/**
 * ----- doRead -----
 * Reads data from FirstApp device.
 * if this is the first read, then go to doWrite next
 * otherwise, go to disConnect next.
 *
 * Callbacks:
 *   doWrite once complete, if it's the first read
 *   doDisconnect once complete, if it's the last read
 *
 * @param   none
 * @return  none
 */
static void doRead(void) {
    if (firstRead) {
        CFirstApp_connectHandler();                     // Do the connectHandler callback.
        firstRead = false;
        PFirstApp_data_read(doWrite);                   // Read initial data, then doWrite
    }
    else {
        PFirstApp_data_read(doDisconnect);              // Read final data, then disconnect
    }
}

/**
 ----- doScan -----
 * Scan for FirstApp peripheral devices.
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
    numFirstAppDevicesSeen = 0;                         // Clear device count before scan.
    firstAppDeviceName[0] = '\0';                       // Clear deviceName before scan.
    CFirstApp_scan(2000, CFirstApp_PFirstApp);          // Scan for FirstApp devices.
}

/**
 ----- doWrite -----
 * Fetches data from buffer, increments and writes back to the FirstApp device
 *
 * Callbacks:
 *   doRead once data transfer complete.
 *
 * @param   none
 * @return  none
 */
static void doWrite(void) {
    data = *PFirstApp_data_iobuf();                     // Read data value out of io buffer
    incrementData();
    *PFirstApp_data_iobuf() = data;                     // Put incremented value into io buffer
    PFirstApp_data_write(doRead);                       // Now write it back to FirstApp device
}

/**
 * ----- incrementData -----
 * Increments the data.
 *
 * @param   none
 * @return  none
 */
static void incrementData(void) {
    data++;
} 

/* -------------------------------------------------------------------------------------------
 *                                  CFirstApp-STUBS.c Callbacks  
 * -------------------------------------------------------------------------------------------
 */

/**
 * ----- CFirstApp_connectHandler -----
 * Called by SRT whenever this CFirstApp device is connected to as a peripheral.
 * Called explicitly in doRead when it connects as a central to an FirstApp device.
 * Turns on the Connected LED.
 *
 * @param   none
 * @return  none
 */
void CFirstApp_connectHandler(void) {
    Hal_connected();
}

/**
 * ----- CFirstApp_disconnectHandler -----
 * Called whenever this CFirstApp device disconnects from another device.  Plus this is called
 * whenever the MCM resets.  So there will always be a callback here upon a reset.
 * Turns off the Connected LED.
 *
 * @param   none
 * @return  none
 */
void CFirstApp_disconnectHandler(void) {
    Hal_disconnected();
}

/**
 * ----- CFirstApp_firstAppDeviceName_fetch -----
 * Called whenever a connected device requests the value of the resource.  Copies the firstAppDeviceName value to output.
 *
 * @param   output - array to store the firstAppDeviceName in.
 * @return  none
 */
void CFirstApp_firstAppDeviceName_fetch(CFirstApp_firstAppDeviceName_t output) {
    memcpy(output, firstAppDeviceName, sizeof(CFirstApp_firstAppDeviceName_t));
}

/**
 * ----- CFirstApp_numFirstAppDevicesSeen_fetch -----
 * Called whenever a connected device requests the value of the resource.  Copies the numFirstAppDevicesSeen value to output.
 *
 *
 * @param   output - pointer to buffer to store numFirstAppDevicesSeen in
 * @return  none
 */
void CFirstApp_numFirstAppDevicesSeen_fetch(CFirstApp_numFirstAppDevicesSeen_t* output) {
    *output = numFirstAppDevicesSeen;
}

/**
 * ----- CFirstApp_scanDoneHandler -----
 * Called whenever a scan operation completes.  
 * If a device was found, copies the name of the device (if found) into firstAppDeviceName.
 * Then goes to doConnect.
 * If not, go back to the idle loop.
 *
 * Callbacks:
 *   doConnect if an FirstApp device was found.
 *
 * @param   numDevices - the number of FirstApp devices seen on the scan
 * @return  none
 */
void CFirstApp_scanDoneHandler(uint8_t numDevices) {
    if (numDevices > 0) {
        memcpy(firstAppDeviceName, curDevice.name, CFirstApp_DeviceName_length);
        doConnect();
    }   
}

/**
 * ----- CFirstApp_data_fetch -----
 * Called whenever a connected device requests the value of the resource.  Copies the data value to output.
 *
 * @param   output - pointer to the buffer to put data in
 * @return  none
 */
void CFirstApp_data_fetch(CFirstApp_data_t* output) {
    *output = data;
}

/* -------------------------------------------------------------------------------------------
 *                                  PFirstApp-STUBS.c Callbacks  
 * -------------------------------------------------------------------------------------------
 */

/**
 * ----- PFirstApp_scanDeviceHandler -----
 * Called whenever a scan operation finds a FirstApp device.  Copies the device descriptor into curDevice.
 * Increments the numFirstAppDevicesSeen.
 *
 * Note:  For this example, this only saves the last device found.  Others are thrown away.  This is simply
 * to minimize storage for small RAM microcontrollers.
 *
 * @param   device - pointer to device descriptor for the FirstApp device found on the scan
 * @return  none
 */
void PFirstApp_scanDeviceHandler(Em_Device* device) {
    numFirstAppDevicesSeen++;
    curDevice = *device;
}
