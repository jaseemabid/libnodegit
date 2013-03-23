lib.Repository.prototype.commit = () ->

    # The plan - Unable to get a reference to the Repository class instance from
    # the Commit instance in C++, so add a Repository.commit with JavaScript,
    # which can pass an additional parameter to the C++ Commit constructor
    # silently - the reference to the repository the commit belongs to.

    # Possibly the dirtiest hack of my life, cant help it! Ship and iterate.
    # Remove this function in the long run.

	console.log "Repository.commit in js"