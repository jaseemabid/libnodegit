lib    = require('../build/Release/libnodegit')
commit = require('./commit.coffee')
_      = require('underscore')

# Adding JavaScript properties to libnodegit
# Leave here as an example
lib.Repository.prototype.foo = () ->
	console.log "foo in js"

# Updating libnodegit with JavaScript properties
module.exports = lib;
