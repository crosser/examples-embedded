'use strict';

var Em;
var Shell;

var Schema = require('../Em/FirstApp.js');							// Load the schema.js file

var sCount;

/* -------- doScan -------- */
function doScan() {
	Shell.log("scanning...");
	Em.ConnectionMgr.scanDevices(500, function (err, devList) {
		var dev = devList[0];
		if (dev && dev.schemaName == 'FirstApp') {
			doOpen(dev);
		}
		else {
			Shell.exit("no device found");
		}
	});
}

/* -------- doOpen -------- */
function doOpen(dev) {
	Em.ConnectionMgr.openDevice(dev, function (err) {
		Shell.log("opened %s", dev.deviceName);
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
	Em.ConnectionMgr.onDisconnect(onDisconnect);
	sCount = args[0] ? Number(args[0]) : 1;
	doScan();
};
