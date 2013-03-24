lib    = require('../build/Release/libnodegit')
_      = require('underscore')

lib.Repository.prototype.commit = (sha) ->
    # OH! my OOP gods, please forgive me for this shit
    #
    # This is supposed to be implemented at C++ layer, and with js. Ideally the
    # Commit constructor should never be exposed, since its just a property of
    # the Repository instance.
    new lib.Commit sha, @path()
