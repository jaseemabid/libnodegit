# Tests, tests, tests!

"use strict";

lib    = require('../build/Release/libnodegit')
_      = require('underscore')

describe "libnodegit", () ->
    it "should return an object", ->
        lib.should.be.an.instanceOf(Object)
    it "should have property Repository", ->
        lib.should.have.property('Repository')

describe "repositories", ->

    before () ->

    it "should open valid repositories", ->
        (() ->
            repo = new lib.Repository("../")
        ).should.not.throw();

    # it "should not open invalid repositories", ->
    #     (() ->
    #         repo = new lib.Repository("/a/b/c")
    #     ).should.throw()

describe "index", () ->

    repo = new lib.Repository("/home/jaseem/Projects/libnodegit")
    index = repo.index()

    it "should return an array", () ->
        index.should.be.an.instanceOf(Array)

    it "should have at least 1 file in it", () ->
        index.length.should.be.above(0)

    it "should have path, sha, size, device, inode, uid, gid, ctime, mtime in it", () ->

        _.all index, (file) ->
            file.should.have.property('path')
            file.should.have.property('sha')
            file.should.have.property('size')
            file.should.have.property('device')
            file.should.have.property('inode')
            file.should.have.property('uid')
            file.should.have.property('gid')
            file.should.have.property('ctime')
            file.should.have.property('mtime')