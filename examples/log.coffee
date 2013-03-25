# $ git log --oneline -10

"use strict";

lib        = require('../lib/index')
_          = require('underscore')
log        = console.log

REPO_VALID = "/home/jaseemabid/Projects/libnodegit"

repo = new lib.Repository(REPO_VALID)
head = repo.head()
commit = repo.commit(head)

console.log "$ git log --oneline -10  \n"

_(10).times (i) ->

    # Read data
    message = commit.message()
    sha = commit.sha()

    # Format for printing
    message = message.substring 0, _.min([message.indexOf('\n'), 80])
    sha = sha.substring(0,7)

    console.log "#{sha} #{message}"

    commit = repo.commit commit.parents()[0]
