#include <node.h>
#include <v8.h>

#include "util.cc"
#include "repository.h"

#include <git2.h>

#include <iostream>

using namespace v8;

Handle<Value> Repository::head(const Arguments& args) {
	HandleScope scope;

	Repository* obj = ObjectWrap::Unwrap<Repository>(args.This());

	return scope.Close(String::New("head"));
}
