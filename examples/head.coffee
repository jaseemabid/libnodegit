# Index!

"use strict";

lib        = require('../lib/index')
_          = require('underscore')
log        = console.log

REPO_VALID = "/home/jaseemabid/Projects/libnodegit"

repo = new lib.Repository(REPO_VALID)
head = repo.head()

console.log "HEAD sha               : ", head.sha()
console.log "HEAD message           : ", head.message()
console.log "HEAD parents           : ", head.parents()
console.log "HEAD Parent[0] message : ", head.parents()[0].message()
