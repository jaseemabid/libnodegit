lib    = require('../build/Release/libnodegit')
_      = require('underscore')

# This file, adds to repository prototype
prototype = lib.Repository.prototype

prototype.commit = (sha) ->
    # Make a new commit object with SHA
    commit = new lib.Commit sha, @path()

    commit.sha = () ->
        # Define commit.sha to return the SHA ID
        # [TODO] Move this to commit file
        sha

    commit.repo = () =>
        # Return parent repo reference
        this

    commit

prototype.head = () ->
    # The function gets the head SHA as a string and returns a reference object
    sha = this.head_()
    this.commit sha
