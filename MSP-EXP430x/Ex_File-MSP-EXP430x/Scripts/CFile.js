'use strict';
/* CFile.js
 * 
 * A NodeJS version of the CFile embedded client app.
 *
 * It will scan for a Blinker device (one or more).
 * Connect to one of them.
 * Read the fileData resource.
 * Increment the received data.
 * Write the data back to the fileData resource
 * Read back the incremented data from the fileData resource.
 * Disconnect from the device
 * 
 */
var sprintf = require('sprintf').sprintf;
var Schema = require('../Em/Ex_File.js');							// Load the schema.js file

// Private data
var Em;
var Shell;
var args;

var curDevice;
var last;

/* -------- doClose -------- 
 * This function will initiate the disconnect.
 * A callback to the onDisconnect function will result.
 */
function doClose() {
	Em.ConnectionMgr.closeDevice();
}

/* -------- doExit -------- 
 * This function will initiate the program exit.
 */
function doExit(msg) {
	Shell.log("Exiting");
	Shell.exit(0);
}

/* -------- doOpen -------- 
 * This function will connect with the specified device found on the scan.
 */
function doOpen() {
	Em.ConnectionMgr.openDevice(curDevice, function (err) {
		Shell.log("Opened '%s', RSSI = %d dBm, Broadcasting:  %s", curDevice.deviceId, 
				curDevice.rssi, (curDevice.broadcast ? JSON.stringify(curDevice.broadcast) : "Off"));
		last = false;
		doRead();
	});
}

/* -------- doRead -------- 
 * This function will read the fileData resource from the Ex_File device and place the data in 
 * fileData variable locally.
 */
function doRead() {
	Em.ConnectionMgr.readResource('fileData', function (err, val) {
		Shell.log("Read %d bytes from 'fileData' on '%s'", val.length, curDevice.deviceName);
		printByteArray(val, {pad: "  "});
		if (!last) {
			doWrite(val);
		}
		else {
			doClose();
		}
	});
}

/* -------- doScan -------- 
 * This function will perform a scan for devices.  
 */
function doScan() {
	curDevice = false;
	Em.ConnectionMgr.scanDevices(500, function (err, devList) {
		Shell.log("Scan for peripheral devices found:  %s", JSON.stringify(devList, ["deviceName"]));
		devList.forEach(function (dev) {
			if (!curDevice && dev.schemaName == "Ex_File" && dev.schemaHash == "236.42.26.0.106.170") {
				curDevice = dev;
			}
		});
		if (curDevice) {
			doOpen();
		}
		else {
			Shell.log("No Ex_File devices found");
			doExit();
		}
	});
}

/* -------- doWrite -------- 
 * This function will write the fileData buffer to the fileData resource on the Ex_File device.
 */
function doWrite(val) {
	for (var i=0; i<val.length; i++) {
		val[i] = (val[i] + 1) & 0xFF;
	}
	Em.ConnectionMgr.writeResource('fileData', val, function (err) {
		Shell.log("Wrote %d bytes to 'fileData' on '%s'", val.length, curDevice.deviceName);
		printByteArray(val, {pad: "  "});
		last = true;
		doRead();
	});
}

/* -------- onDisconnect -------- 
 * This function is called whenever a disconnect message is received from the device. 
 */
function onDisconnect() {
	Shell.log("Closed");
	doExit();
}

/* -------- onIndicator -------- 
 * This function is called whenever an indicator is received from the device. 
 */
function onIndicator(name, val) {
   	Shell.log("** Indicator received: %s = %s", name, val);
}

/* -------- printByteArray -------- 
 * This function will print out an array of bytes.
 * val is the array.
 * attributes is an object with elements:
 *   pad:  A string to print at the beginning of each output line
 *   format:  hex or dec for printout format
 * prints up to 16 bytes per output line.
 */
function printByteArray(val, attributes) {
	// Set default parameter values
	if (typeof attributes === 'undefined') {
		attributes = {};
	}
	if (typeof attributes.pad === 'undefined') { 
		attributes.pad = "";
	}
	if (typeof attributes.format === 'undefined') {
		attributes.format = "dec";
	}
	// Figure out how many digits are needed for the left index and the right index for the lines.
	var BYTES_PER_LINE = 16;
	var largestLeftIndex = Math.floor((val.length-1) / BYTES_PER_LINE) * BYTES_PER_LINE;
	var largestRightIndex = val.length - 1;
	var numDigitsLeft = 0;
	var numDigitsRight = 0;
	for (var x=largestLeftIndex; x>0; x=Math.floor(x/10)) {		// calculate number of digits for left index
		numDigitsLeft++;
	}
	for (var x=largestRightIndex; x>0; x=Math.floor(x/10)) {	// calculate number of digits for right index
		numDigitsRight++;
	}
	numDigitsLeft = Math.max(1, numDigitsLeft);					// A zero needs a digit too.
	numDigitsRight = Math.max(1, numDigitsRight);				// A zero needs a digit too.
	var rangeFormatString = "%s[%" + numDigitsLeft + "d..%" + numDigitsRight + "d]:";
	// Now print out the lines
	for (var i=0; i<val.length; i+=BYTES_PER_LINE) {
		var lineLength = Math.min((val.length - i), BYTES_PER_LINE);
		var line = sprintf(rangeFormatString, attributes.pad, i, i+lineLength-1);
		for (var j=0; j<lineLength; j++) {
			switch (attributes.format) {
			case "hex":
				line += sprintf(" %02X", val[i+j]);
				break;
			case "dec": 
			default:
				line += sprintf(" %3d", val[i+j]);
				break;
			}
		}
		Shell.log(line);
	}
}

/* -------- run -------- 
 * This function is the main entry point.  
 *   args is an array of the input parameters -- NULL if no parameters input.
 *   shellMod is the console object to use for outputs.
 *   EmMod is the Emmoco object
 */
function run(args, shellMod, emMod) {
	Shell = shellMod;												// Save the Shell object
	Em = emMod;														// Save the Em object
    Em.ConnectionMgr.addSchema(Schema);								// Add the schema for scanning
	Em.ConnectionMgr.onDisconnect(onDisconnect);					// Setup the onDisconnect handler
	Em.ConnectionMgr.onIndicator(onIndicator);						// Setup the onIndicator handler
	doScan();														// Start the scanning
};

/* -------- export entry point -------- */
if ('undefined' !== typeof exports) exports.run = run;
