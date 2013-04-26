# Tests, tests, tests!

"use strict";

lib        = require('../lib/index')
_          = require('underscore')

describe "libnodegit", () ->
    it "should return an object", ->
        lib.should.be.an.instanceOf(Object)
    it "should have property Repository", ->
        lib.should.have.property('Repository')
    it "should have property Commit", ->
        lib.should.have.property('Commit')
