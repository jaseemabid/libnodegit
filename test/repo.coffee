# Tests, tests, tests!

"use strict";

lib          = require('../lib/index')
_            = require('underscore')
log          = console.log
defaults     = require('./defaults')

repo_bare    = new lib.Repository defaults.repo_bare_path
repo_empty   = new lib.Repository defaults.repo_empty_path
repo_valid   = new lib.Repository defaults.repo_valid_path

describe "Repository", ->

    it "should open valid repositories", ->
        (() ->
            repo_valid = new lib.Repository(defaults.repo_valid_path)
        ).should.not.throw();

    it "should not open invalid repositories", ->
        (() ->
            repo_invalid = new lib.Repository defaults.repo_invalid_path
        ).should.throw()

    describe "isBare", ->
        it "should return a boolean", ->
           _.each [repo_valid, repo_bare, repo_empty], (repo) ->
              repo.isBare().should.be.a('boolean')

        it "should return true for bare repo", ->
            repo_bare.isBare().should.be.true

        it "should return false for non bare", ->
            repo_valid.isBare().should.not.be.true

    describe "isEmpty", ->
        it "should return a boolean", ->
           _.each [repo_valid, repo_bare, repo_empty], (repo) ->
              repo.isEmpty().should.be.a('boolean')

        it "should return true for empty repo", ->
            repo_empty.isEmpty().should.be.true

        it "should return false for non empty", ->
            repo_valid.isEmpty().should.not.be.true

    describe "index", () ->
        index = repo_valid.index()

        it "should return an array", () ->
            index.should.be.an.instanceOf(Array)

        it "should have at least 1 file in it", () ->
            index.length.should.be.above(0)

        it "should have property path", () ->
            _.all index, (file) ->
                file.should.have.property('path')
                file.path.should.be.a 'string'

        it "should have property sha", () ->
            _.all index, (file) ->
                file.should.have.property('sha')
                file.sha.should.be.a 'string'
                file.sha.should.have.length 40

        it "should have property size", () ->
            _.all index, (file) ->
                file.should.have.property('size')

        it "should have properties device, inode, uid, gid, ctime and mtime", () ->
            _.all index, (file) ->
                file.should.have.property('device')
                file.should.have.property('inode')
                file.should.have.property('uid')
                file.should.have.property('gid')
                file.should.have.property('ctime')
                file.should.have.property('mtime')

    describe "head", () ->
        head = repo_valid.head()

        it "should return a commit instance", () ->
            head.should.be.an.instanceOf lib.Commit

    describe "log", () ->
        repo_log = repo_valid.log()

        it "should return an array", () ->
            repo_log.should.be.an.instanceOf(Array)

        it "should return commit instances", () ->
            _.each repo_log, (commit) ->
                commit.should.be.an.instanceOf lib.Commit
