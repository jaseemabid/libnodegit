#!/bin/bash

# only watches first parameter for modification
while inotifywait -e modify $1 ; do
        echo
		clear;
		node-gyp build
		date
		node examples/index.js
done
