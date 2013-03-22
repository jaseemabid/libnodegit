# Index!

"use strict";

lib        = require('../build/Release/libnodegit')
_          = require('underscore')
log        = console.log

REPO_VALID = "/home/jaseemabid/Projects/libnodegit"

repo = new lib.Repository(REPO_VALID)
head = repo.head()

console.log " HEAD: ", head
