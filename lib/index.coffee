lib    = require('../build/Release/libnodegit')
commit = require('./commit')
_      = require('underscore')

# Adding JavaScript properties to libnodegit

lib.Repository.prototype.head = () ->
  console.log "head "
  # The function gets the head SHA as a string and returns a reference object
  sha = this.head_()
  this.commit sha

# Updating libnodegit with JavaScript properties
module.exports = lib;
