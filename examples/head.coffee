# Index!

"use strict";

lib        = require('../lib/index')
_          = require('underscore')
log        = console.log

REPO_VALID = "/home/jaseemabid/Projects/libnodegit"

repo = new lib.Repository(REPO_VALID)
head = repo.head()
commit = new lib.Commit(head, REPO_VALID);

console.log "REPO         : ", repo
console.log "REPO path    : ", repo.path()
console.log "HEAD sha     : ", head
console.log "HEAD message : ", commit.message()
