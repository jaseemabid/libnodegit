lib    = require('../build/Release/libnodegit')
commit = require('./commit.coffee')
_      = require('underscore')

# Adding JavaScript properties to libnodegit

lib.Repository.prototype.head = () ->
  console.log "head "
  this.head_()

# Updating libnodegit with JavaScript properties
module.exports = lib;
