'use strict';

var Em;
var Shell;

var Schema = require('../Em/Blinker.js');							// Load the schema.js file

var sDevice;
var sSecs;

/* -------- doScan -------- */
function doScan() {
	Shell.log("scanning...");
	Em.ConnectionMgr.scanDevices(500, function (err, devList) {
		for (var i = 0; i < devList.length; i++) {
			var dev = devList[i];
			Shell.log("found %s, rssi = %d", dev.deviceId, dev.rssi);
			if (dev.schemaId != null) {
				sDevice = dev;
			}
		}			
		if (sDevice) {
			doOpen();
		}
		else {
			Shell.exit("no Blinker device found");
		}
	});
}

/* -------- doOpen -------- */
function doOpen() {
	Em.ConnectionMgr.openDevice(sDevice, function (err) {
		Shell.log("opened %s", sDevice.deviceName);
		Shell.log("closing in %d secs...", sSecs);
		setTimeout(function () {
			doClose();
		}, sSecs * 1000);
	});
}

/* -------- doClose -------- */
function doClose() {
	Em.ConnectionMgr.closeDevice();
}

/* -------- onDisconnect -------- */
function onDisconnect() {
	Shell.log("disconnected");
	Shell.exit();
}

/* -------- onIndicator -------- */
function onIndicator(name, val) {
	Shell.log("indicator: %s = %s", name, val);
}

/* -------- run -------- */
exports.run = function(args, Shell_M, Em_M) {
	Shell = Shell_M;
	Em = Em_M;
    Em.ConnectionMgr.addSchema(Schema);
	Em.ConnectionMgr.onDisconnect(onDisconnect);
	Em.ConnectionMgr.onIndicator(onIndicator);
	sSecs = args[0] ? Number(args[0]) : 10;
	doScan();
};
