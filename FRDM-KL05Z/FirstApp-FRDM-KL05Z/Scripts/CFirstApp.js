'use strict';

var Em;
var Shell;

var Schema = require('../Em/FirstApp.js');							// Load the schema.js file

var sCount;
var sDevice

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
			Shell.exit("no FirstApp device found");
		}
	});
}

/* -------- doOpen -------- */
function doOpen(dev) {
	Em.ConnectionMgr.openDevice(sDevice, function (err) {
		Shell.log("opened %s", sDevice.deviceName);
		doRead();
	});
}

/* -------- doRead -------- */
function doRead() {
	Em.ConnectionMgr.readResource('data', function (err, val) {
		Shell.log("read: data = %d, count = %d", val, sCount);
		if (sCount--) {
			doWrite(val + 1);
		}
		else {
			doClose();
		}
	});
}

/* -------- doWrite -------- */
function doWrite(val) {
	Em.ConnectionMgr.writeResource('data', val, function (err) {
		Shell.log("write done");
		doRead();
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

/* -------- run -------- */
exports.run = function(args, Shell_M, Em_M) {
	Shell = Shell_M;
	Em = Em_M;
    Em.ConnectionMgr.addSchema(Schema);
	Em.ConnectionMgr.onDisconnect(onDisconnect);
	sCount = args[0] ? Number(args[0]) : 3;
	doScan();
};
