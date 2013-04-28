# $ git log --oneline -10

"use strict";

lib        = require('../lib/index')
_          = require('underscore')

REPO_VALID = "/home/jaseemabid/Projects/libnodegit"

repo = new lib.Repository(REPO_VALID)
log  = repo.log
    count: 10

console.log "$ git log --oneline -10  \n"

_.each log, (commit) ->

    # Read data
    message = commit.message()
    sha = commit.sha()

    # Format for printing
    message = message.substring 0, _.min([message.indexOf('\n'), 80])
    sha = sha.substring(0,7)

    console.log "#{sha} #{message}"
