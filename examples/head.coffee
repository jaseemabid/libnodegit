# Index!

"use strict";

lib        = require('../build/Release/libnodegit')
_          = require('underscore')
log        = console.log

REPO_VALID = "/home/jaseemabid/Projects/libnodegit"

repo = new lib.Repository(REPO_VALID)
head = repo.head()
commit = new lib.Commit(head);

console.log "HEAD sha     : ", head
console.log "HEAD message : ", commit.message()
