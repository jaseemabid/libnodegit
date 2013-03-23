# Index!

"use strict";

lib        = require('../lib/index.js')
_          = require('underscore')
log        = console.log

REPO_VALID = "/home/jaseemabid/Projects/libnodegit"

repo = new lib.Repository(REPO_VALID)
index = repo.index()

console.log " SHA    | Path  "
console.log " ------------------------"
_.each index, (file) ->
    console.log " #{file.sha.slice(0,6)} | #{file.path}"