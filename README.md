# libnodegit

libnodegit is asynchronous git bindings for node.js inspired by the similar
projects [node-gitteh](https://github.com/libgit2/node-gitteh) and
[nodegit](https://github.com/tbranyen/nodegit). It is built using the
[libgit2](http://libgit2.github.com/) library.

More information is there on the wiki.

## Installation

Mac OS X/Linux/Unix
Install nodegit by cloning source from GitHub.
TODO: Add makefiles to automate this?

*Note: nodegit assumes your library path exists at ~/.node_libraries you can
 change this by specifying a new lib path*

	# Install node.js
	# Install libgit2
	$ git clone https://github.com/jaseemabid/libnodegit.git libnodegit
	$ npm install ./libnodegit


## Running tests

	$ cd libnodegit
	$ npm test

## Lint

	$ cd libnodegit
	$ npm lint

## Freemind map

	There is an org-mode file
	[here](https://github.com/jaseemabid/libnodegit/wiki/libnodegit.org). Export
	it to freemind map by *M-x org-export-as-freemind* in emacs.

## Project milestones [here](https://github.com/jaseemabid/libnodegit/wiki/Milestones)
