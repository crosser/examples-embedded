/**
 *  ----- CFile-Prog.c ----- 
 * 
 * This example program demonstrates operating as a central in conjunction with a peripheral doing file transfers.
 *
 * Non-Blocking Technique Used:
 * ============================
 * It is very important to note that operation as a central node is done with a non-blocking, event-driven technique
 * using callbacks.  So an action is started, and essentially immediately returns to the idle loop.  When the action is
 * completed, a callback is issued to determine what (if any) the next action should be.
 *
 * Some of the callbacks are explicit (specified in the call to start the action).  And some of the callbacks are 
 * implicit (given by the specific action started).  For example,
 *   CFile_scan -- implicit callbacks to scanDeviceHandler and scanDoneHandler
 *   PFile_connect -- explicit success callback specified in call -- implicit failure callback to CFile_disconnectHandler().
 * 
 * CFile Example Operation:
 * ========================
 * Upon a button push, this example "scans" for a peripheral device running the Ex_File schema (as specified in the schema.properties file).
 * As it scans it records the number of such devices found, and for this example, it records the descriptor of
 * the last such device found.  
 * If no such devices are found, the program goes back to the idle loop.
 * If it finds at least one such device, then it will do the following:
 *   connect to the last such device found (and remember that there is no ordering to those found).
 *   read all the file data from the device found (blinking the LED for each callback to storeFileData)
 *   increment the data read
 *   write it back to the device found (toggling the LED for each callback to fetchFileData)
 *   read the file data from the device found again (with LED blink) to see that the incremented data was written properly
 *   go back to idle state awaiting the next button push
 *
 * Notes:
 * The size of the file transferred is controlled by the Ex_File device's fileSize resource.  It defaults to 10 bytes, but can be
 * set to a file of arbitrary size.
 *
 * For this demo, only the first byte of the file transferred is actually stored, incremented, etc.  The reason for only storing the first byte 
 * is so that this demo will run using very little RAM memory on the microcontroller.
 *
 * Once the CFile program returns to the idle state awaiting a button push, it is operating as a peripheral.  As such, it can be
 * connected to (by Em-Browser for example), and the data in the CFile.ems schema can be examined.  For example, after each "run"
 * caused by a button push, the seed value should increment by one.  And the deviceName of the Ex_File device should be present.
 *
 * CFile to Ex_File Resource Data Transfers:
 * =========================================
 * For any resources transferred between this CFile device and the Ex_File device connected, the data transfer goes through an I/O buffer.
 * As such, 
 *   before an over-the-air write from CFile to Ex_File, the data to be transferred must be placed in iobuf
 *   and after an over-the-air read from Ex_FIle into CFile, the data transferred must be copied out of iobuf for storage.
 *
 * File Tranfer Method Details:
 * ============================
 * File transfers are a special case because they cannot necessarily be completed in one over-the-air transaction.
 * Because files can be of arbitrary length, the Schema Run Time (SRT) code will break the file transfer up into pieces automatically.
 *
 * Consider that there are two devices (the CFile central, and the Ex_File peripheral).  Each has local storage for its file data,
 * and here on CFile, there is an intermediate buffer iobuf that contains the pieces of the file currently being tranferred.
 * As such, there are several methods used in effecting the file transfer:
 *
 * On this CFile device:
 *  fecthFileData:          Fetch from local storage, and place in iobuf.
 *  storeFileData:          Take data in iobuf and store to local storage.
 *  PFIle_fileData_read:    Read file from Ex_File device, and call storeFileData (zero or more times) to place into local storage.
 *                          * On the Ex_File device this will result in one or more calls to Ex_File_fileData_fetch().
 *  PFile_fileData_Write:   call fetchFileData one or more times to retrieve from local storage, then write to the Ex_File device.
 *                          * On the Ex_File device, this will result in one or more calls to Ex_File_fileData_store().
 *
 * Here are the details of how the operation works:
 * There are really two transfer cases:  
 *   Fetching out of storage and writing to the Ex_File device over the air.
 *   Reading over-the-air from the Ex_File device and storing into storage.
 *
 * For the fetching from storage and writing to Ex_File case:
 *   The SRT will call the "fetch" callback (in this example fetchFileData) with three parameters:
 *     offset (the starting byte offset in the file for this callback instance)
 *     count (the maximum number of bytes to read out of storage and place in iobuf)
 *     iobuf (a pointer to the iobuf buffer)
 *   The "fetch" callback should copy the count bytes (less if end-of-file) from local storage into iobuf, and then return the number of bytes copied.
 *   The SRT will continue to issue fetch callbacks until the "fetch" callback returns a number less than count -- indicating end-of-file.
 *
 * For the reading from Ex_File and storing into storage case:
 *   The SRT will call the "store" callback (in this example storeFileData) with three parameters:
 *     offset (the starting byte offset in the file for this callback instance)
 *     count (the number of bytes to contained in iobuf)
 *     iobuf (a pointer to the iobuf buffer)
 *   The "store" callback will copy count bytes out of iobuf and into storage, and then return the number of bytes copied.
 *   The SRT will continue to issue callbacks until all the data has been transferred.
 *
 * For either the writing or reading case, when the file transfer is complete, a final file-transfer-complete callback will be issued. 
 * Hence there are two callbacks on the: CFile_fileData_write and CFile_fileData_read methods.
 *
 */
#include "CFile.h"
#include "Hal.h"

// Private Method Prototypes
static void buttonHandler(void);
static void doDisconnect(void);
static void doRead(void);
static void doScan(void);
static void doWrite(void);
static uint16_t fetchFileData(uint8_t*, int32_t, uint16_t);
static void incrementFileData(void);
static uint16_t storeFileData(uint8_t*, int32_t, uint16_t);

// Schema Data -- available when CFile device not connected to Ex_File device.
CFile_Ex_FileDeviceName_t Ex_FileDeviceName;                // Name of Ex_File device last connected
CFile_numBytesRead_t numBytesRead;                          // Number of bytes read on last file transfer
CFile_numEx_FileDevicesSeen_t numEx_FileDevicesSeen = 0;    // Number of Ex_File devices seen on last scan
CFile_seed_t seed;                                          // first byte of last file read 

// Private Data
Em_Device curDevice;                                        // Current device descriptor
bool firstRead = true;                                      // Is this the first read or the last read

/**
 * ----- main -----
 * Initialize device, enable button interrupt / handler, start Schema RunTime, and go into Idle loop awaiting events
 */ 
void main() {
    Hal_init();                                     // Set initial hardware conditions
    Hal_buttonEnable(buttonHandler);                // Set up button handler as callback when button pressed
    CFile_start();                                  // Start up the MCM
    Hal_idleLoop();                                 // Await events -- which basically means wait for a button push.
}

/* -------------------------------------------------------------------------------------------
 *                                       Private Methods  
 * -------------------------------------------------------------------------------------------
 */

/**
 * ----- buttonHandler -----
 * 
 * Issue half-second LED to acknowledge button push
 * Then, do a scan for Ex_File devices.
 *
 * @param   none
 * @return  none
 */
static void buttonHandler(void) {
    Hal_ledOn();
    Hal_delay(500);                                 // Give half-second LED to indicate button push
    Hal_ledOff();
    doScan();
}

/**
 * ----- doConnect -----
 * Attempts to connect to the Ex_File device found.
 *
 * Callbacks:
 *   doRead if connected
 *   CFile_disconnectHandler() if not.
 *
 * @param   none
 * @return  none
 */
static void doConnect(void) {
// PFile_connect will attempt to connect to curDevice for 10s
// Note bug EM-63:  the timeout is not yet implemented.  So it will attempt to connect forever.
    firstRead = true;
    PFile_connect(&curDevice, 10, doRead);
}

/**
 * ----- doDisconnect -----
 * Disconnects from Ex_File device.
 *
 * Callback:
 *   Implicit callback to CFile_disconnectHandler once complete.
 *
 * @param   none
 * @return  none
 */
static void doDisconnect(void) {
    CFile_disconnect();                             // Disconnect from peripheral device
}

/**
 * ----- doRead -----
 * Reads file from Ex_File device and stores first byte into seed.
 * if this is the first read, then go to doWrite next
 * otherwise, go to disConnect next.
 *
 * Callbacks:
 *   storeFileData with each piece of the file.
 *   doWrite once complete, if it's the first read
 *   doDisconnect once complete, if it's the last read
 *
 * @param   none
 * @return  none
 */
static void doRead(void) {
    numBytesRead = 0;                                       // Reset the numBytesRead counter.
    
    if (firstRead) {
        CFile_connectHandler();                             // Do the connectHandler callback.
        firstRead = false;
        PFile_fileData_read(storeFileData, doWrite);        // Read initial data, then doWrite
    }
    else {
        PFile_fileData_read(storeFileData, doDisconnect);   // Read final data, then disconnect
    }
}

/**
 ----- doScan -----
 * Scan for Ex_File peripheral devices.
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
    numEx_FileDevicesSeen = 0;                      // Clear device count before scan.
    Ex_FileDeviceName[0] = '\0';                    // Clear deviceName before scan.
    CFile_scan(2000, CFile_PFile);                  // Scan for Ex_File devices.
}

/**
 ----- doWrite -----
 * Fetches data from local storage, and writes file to the Ex_File device
 *
 * Callbacks:
 *   fetchFileData for each piece of the file.
 *   doRead once file transfer complete.
 *
 * @param   none
 * @return  none
 */
static void doWrite(void) {
    incrementFileData();
    PFile_fileData_write(fetchFileData, doRead);
}

/**
 * ----- fetchFileData -----
 * Fetches up to count bytes beginning at offset from local storage and copies into iobuf.
 * Returns the number of bytes copied.
 *
 * Toggles LED to show activity
 *
 * Note:  For this demo, only fetches the first byte from local storage.  After that it just sends an incrementing pattern.
 *   This allows the program to fit in the small RAM microcontrollers.
 *
 * @param   iobuf - pointer to i/o buffer
 * @param   offset - byte offset within file to start fetch
 * @param   count - maximum number of bytes to put in iobuf
 * @return  number of bytes put into iobuf
 */
static uint16_t fetchFileData(uint8_t* iobuf, int32_t offset, uint16_t count) {
    int32_t bytesLeftToGo = numBytesRead - offset;      // for this example, we write back the same number of bytes read
    Hal_ledToggle();
    if (bytesLeftToGo < count) {
        count = (uint16_t)bytesLeftToGo;
    }
    for (uint8_t i = 0; i < count; i++) {
        iobuf[i] = (seed + offset + i) & 0xFF;          // normally would fetch the data here, instead generate a pattern
    }
    return count;
} 

/**
 * ----- incrementFileData -----
 * Increments the stored file data.
 * Note that for this example, that simply means incrementing the seed.
 *
 * @param   none
 * @return  none
 */
static void incrementFileData(void) {
    seed = (seed + 1) & 0xFF;
} 

/**
 * ----- storeFileData -----
 * Stores count bytes beginning at offset from iobuf and copies into local storage.
 * Returns the number of bytes copied.
 *
 * Blinks LED to show activity.
 *
 * Note:  For this demo, only stores the first byte into local storage.  After that it just throws them away.
 *   This allows the program to fit in the small RAM microcontrollers.
 *
 * @param   iobuf - pointer to i/o buffer
 * @param   offset - byte offset within file to start store
 * @param   count - number of bytes in iobuf to store
 * @return  number of bytes copied out of iobuf
 */
static uint16_t storeFileData(uint8_t* iobuf, int32_t offset, uint16_t count) {
    Hal_ledOn();
    if (offset == 0) {
        seed = iobuf[0];                            // for this example, just store the byte 0 of the file
    }
    for (uint8_t i = 0; i < count; i++) {
                                                    // normally could store the data here, but throw away instead.
    }
    numBytesRead += count;                          // bump the local filesize counter
    Hal_ledOff();
    return count;
} 

/* -------------------------------------------------------------------------------------------
 *                                  CFile-STUBS.c Callbacks  
 * -------------------------------------------------------------------------------------------
 */

/**
 * ----- CFile_connectHandler -----
 * Called by SRT whenever this CFile device is connected to as a peripheral.
 * Called explicitly in doRead when it connects as a central to an Ex_FIle device.
 * Turns on the Connected LED.
 *
 * @param   none
 * @return  none
 */
void CFile_connectHandler(void) {
    Hal_connected();
}

/**
 * ----- CFile_disconnectHandler -----
 * Called whenever this CFile device disconnects from another device.  Plus this is called
 * whenever the MCM resets.  So there will always be a callback here upon a reset.
 * Turns off the Connected LED.
 *
 * @param   none
 * @return  none
 */
void CFile_disconnectHandler(void) {
    Hal_disconnected();
}

/**
 * ----- CFile_Ex_FileDeviceName_fetch -----
 * Called whenever a connected device requests the value of the resource.  Copies the Ex_FileDeviceName value to output.
 *
 * @param   output - array to store the Ex_FileDeviceName in.
 * @return  none
 */
void CFile_Ex_FileDeviceName_fetch(CFile_Ex_FileDeviceName_t output) {
    memcpy(output, Ex_FileDeviceName, sizeof(CFile_Ex_FileDeviceName_t));
}

/**
 * ----- CFile_numBytesRead_fetch -----
 * Called whenever a connected device requests the value of the resource.  Copies the numBytesRead value to output.
 *
 * @param   output - pointer to buffer to store numBytesRead in
 * @return  none
 */
void CFile_numBytesRead_fetch(CFile_numBytesRead_t* output) {
    *output = numBytesRead;
}

/**
 * ----- CFile_numEx_FileDevicesSeen_fetch -----
 * Called whenever a connected device requests the value of the resource.  Copies the numExFileDevicesSeen value to output.
 *
 *
 * @param   output - pointer to buffer to store numEx_FileDevicesSeen in
 * @return  none
 */
void CFile_numEx_FileDevicesSeen_fetch(CFile_numEx_FileDevicesSeen_t* output) {
    *output = numEx_FileDevicesSeen;
}

/**
 * ----- CFile_scanDoneHandler -----
 * Called whenever a scan operation completes.  
 * If a device was found, copies the name of the device (if found) into Ex_FileDeviceName.
 * Then goes to doConnect.
 * If not, go back to the idle loop.
 *
 * Callbacks:
 *   doConnect if an Ex_File device was found.
 *   doScan if not.
 *
 * @param   numDevices - the number of Ex_File devices seen on the scan
 * @return  none
 */
void CFile_scanDoneHandler(uint8_t numDevices) {
    if (numDevices > 0) {
        memcpy(Ex_FileDeviceName, curDevice.name, CFile_DeviceName_length);
        doConnect();
    }   
}

/**
 * ----- CFile_seed_fetch -----
 * Called whenever a connected device requests the value of the resource.  Copies the seed value to output.
 *
 * @param   output - pointer to the buffer to put seed in
 * @return  none
 */
void CFile_seed_fetch(CFile_seed_t* output) {
    *output = seed;
}

/* -------------------------------------------------------------------------------------------
 *                                  PFile-STUBS.c Callbacks  
 * -------------------------------------------------------------------------------------------
 */

/**
 * ----- PFile_scanDeviceHandler -----
 * Called whenever a scan operation finds an Ex_File device.  Copies the device descriptor into curDevice.
 * Increments the numEx_FileDevicesSeen.
 *
 * Note:  For this example, this only saves the last device found.  Others are thrown away.  This is simply
 * to minimize storage for the MSP430G2553.
 *
 * @param   device - pointer to device descriptor for the Ex_File device found on the scan
 * @return  none
 */
void PFile_scanDeviceHandler(Em_Device* device) {
    numEx_FileDevicesSeen++;
    curDevice = *device;
}
