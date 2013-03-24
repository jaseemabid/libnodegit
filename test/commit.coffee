# Tests, tests, tests!

"use strict";

lib        = require('../lib/index')
_          = require('underscore')
log        = console.log
def        = require('./defaults')

REPO_VALID = def.REPO_VALID
REPO_BARE  = def.REPO_BARE
REPO_EMPTY = def.REPO_EMPTY

COMMIT_VALID   = "1de0f007cbfb661f4075601b3139a18c72a0b0e4"
COMMIT_INVALID = "this-is-an-invalid-commit-SHAid-for-sure"

describe "Commit", ->

    it "should read valid commits", ->
        (() ->
            commit = new lib.Commit(COMMIT_VALID, REPO_VALID)
        ).should.not.throw();

    it "should not read invalid commits", ->
        (() ->
            commit = new lib.Commit(COMMIT_INVALID, REPO_VALID)
        ).should.throw()


    describe "parents", ->
        it "should return an array", ->
            commit = new lib.Commit(COMMIT_VALID, REPO_VALID)
            commit.parents().should.be.an.instanceOf(Array)
        it "should have atleast one parent", ->
            commit = new lib.Commit(COMMIT_VALID, REPO_VALID)
            commit.parents().should.have.length(1)
        it "should have have valid sha ID", ->
            commit = new lib.Commit(COMMIT_VALID, REPO_VALID)
            _.each commit.parents(), (parent) ->
                parent.should.be.a('string')
                parent.should.have.length(40)

    describe "message", ->
        it "should return a string", ->
            commit = new lib.Commit(COMMIT_VALID, REPO_VALID)
            commit.message().should.be.a('string')
