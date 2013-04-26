lib    = require('../build/Release/libnodegit')
_      = require('underscore')


# Adding JavaScript properties to libnodegit

repository = require('./repository')
commit     = require('./commit')

# Updating libnodegit with JavaScript properties
module.exports = lib;
