var lib = require('../build/Release/libnodegit'),
	_ = require('underscore');

// Adding JavaScript properties to libnodegit
lib.Repository.prototype.foo = function() {
	console.log("foo in js");
};

// Updating libnodegit with JavaScript properties
module.exports = lib;