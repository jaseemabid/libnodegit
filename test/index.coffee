# Tests, tests, tests!

"use strict";

libnodegit = require('../build/Release/libnodegit')
assert     = require('assert')
_          = require('underscore')

describe "nodelibgit", () ->
        Object.keys(libnodegit).should.be.an.instanceOf(Array)

describe "repositories", ->

    before () ->

    it "should open valid repositories", ->

        (
            () ->
                index = libnodegit.index("/home/jaseem/Projects/libnodegit")
        ).should.not.throw();

    it "should not open invalid repositories", ->

        (
            () ->
                index = libnodegit.index("/some/stupid/path")
        ).should.throw();


describe "index", () ->

    before () ->


    it "should return an array", () ->
        index = libnodegit.index("/home/jaseem/Projects/libnodegit")
        index.should.be.an.instanceOf(Array)
