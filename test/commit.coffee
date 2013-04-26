# Tests, tests, tests!

"use strict";

lib            = require('../lib/index')
_              = require('underscore')
defaults       = require('./defaults')

COMMIT_VALID   = "1de0f007cbfb661f4075601b3139a18c72a0b0e4"
COMMIT_INVALID = "this-is-an-invalid-commit-SHAid-for-sure"

repo_bare      = new lib.Repository defaults.repo_bare_path
repo_empty     = new lib.Repository defaults.repo_empty_path
repo_valid     = new lib.Repository defaults.repo_valid_path

commit_valid   = new lib.Commit(COMMIT_VALID, defaults.repo_valid_path)

describe "Commit", ->

    it "should read valid commits", ->
        (() ->
            commit = new lib.Commit(COMMIT_VALID, defaults.repo_valid_path)
        ).should.not.throw();

    it "should not read invalid commits", ->
        (() ->
            commit = new lib.Commit(COMMIT_INVALID, defaults.repo_valid_path)
        ).should.throw()

    describe "parents", ->
        it "should return an array", ->
            commit_valid.parents().should.be.an.instanceOf(Array)
        it "should have atleast one parent", ->
            commit_valid.parents().should.have.length(1)
        it "should have have valid sha ID", ->
            commit = new lib.Commit(COMMIT_VALID, defaults.repo_valid_path)
            _.each commit_valid.parents(), (parent) ->
                parent.should.be.a('string')
                parent.should.have.length(40)

    describe "message", ->
        it "should return a string", ->
            commit_valid.message().should.be.a('string')
