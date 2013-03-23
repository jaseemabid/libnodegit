# Tests, tests, tests!

"use strict";

lib        = require('../lib/index')
_          = require('underscore')
log        = console.log
def        = require('./defaults')

REPO_VALID = def.REPO_VALID
REPO_BARE  = def.REPO_BARE
REPO_EMPTY = def.REPO_EMPTY

describe "Repository", ->

    it "should open valid repositories", ->
        (() ->
            repo = new lib.Repository(REPO_VALID)
        ).should.not.throw();

    it "should not open invalid repositories", ->
        (() ->
            repo = new lib.Repository("/a/b/c")
        ).should.throw()

    describe "isBare", ->
        it "should return a boolean", ->
            repo = new lib.Repository(REPO_VALID)
            repo.isBare().should.be.a('boolean')

        it "should return true for bare repo", ->
            repo = new lib.Repository(REPO_BARE)
            repo.isBare().should.be.true

        it "should return false for non bare", ->
            repo = new lib.Repository(REPO_VALID)
            repo.isBare().should.not.be.true


    describe "isEmpty", ->
        it "should return a boolean", ->
            repo = new lib.Repository(REPO_VALID)
            repo.isEmpty().should.be.a('boolean')

        it "should return true for empty repo", ->
            repo = new lib.Repository(REPO_EMPTY)
            repo.isEmpty().should.be.true

        it "should return false for non empty", ->
            repo = new lib.Repository(REPO_VALID)
            repo.isEmpty().should.not.be.true


    describe "index", () ->
        repo = new lib.Repository(REPO_VALID)
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
