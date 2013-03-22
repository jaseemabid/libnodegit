# Index!

"use strict";

lib        = require('../build/Release/libnodegit')
_          = require('underscore')
log        = console.log

REPO_VALID = "/home/jaseemabid/Projects/libnodegit"

commit = new lib.Commit("361666a55ab643ca9e68de6cc44f800627c002e3");

console.log " Commit: ", commit
console.log " Commit.sha: ", commit.sha()