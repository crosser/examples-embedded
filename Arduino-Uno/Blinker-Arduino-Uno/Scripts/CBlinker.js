'use strict';

var Em;
var Shell;

var Schema = require('../Em/Blinker.js');							// Load the schema.js file

var sSecs;

/* -------- doScan -------- */
function doScan() {
	Shell.log("scanning...");
	Em.ConnectionMgr.scanDevices(500, function (err, devList) {
		var dev = devList[0];
		if (dev && dev.schemaName == 'Blinker') {
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
	Em.ConnectionMgr.onDisconnect(onDisconnect);
	Em.ConnectionMgr.onIndicator(onIndicator);
	sSecs = args[0] ? Number(args[0]) : 10;
	doScan();
};
