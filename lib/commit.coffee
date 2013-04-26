lib    = require('../build/Release/libnodegit')
_      = require('underscore')


# This file, adds to repository prototype
prototype = lib.Commit.prototype

prototype.parents = () ->

    # The function gets the head SHA as a string and returns a reference object
    # sha = this.head_()
    # this.commit sha

    plist = _.map @parents_(), (parent) =>
        @repo().commit parent

    plist
