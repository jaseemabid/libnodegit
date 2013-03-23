# Tests, tests, tests!

"use strict";

lib        = require('../lib/index.js')
_          = require('underscore')
log        = console.log
def        = require('./defaults')

REPO_VALID = def.REPO_VALID
REPO_BARE  = def.REPO_BARE
REPO_EMPTY = def.REPO_EMPTY

describe "libnodegit", () ->
    it "should return an object", ->
        lib.should.be.an.instanceOf(Object)
    it "should have property Repository", ->
        lib.should.have.property('Repository')
    it "should have property Commit", ->
        lib.should.have.property('Commit')
