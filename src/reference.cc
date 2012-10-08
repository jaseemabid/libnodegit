#include <node.h>
#include <v8.h>

#include "util.cc"
#include "reference.h"

#include <git2.h>

#include <iostream>

using namespace v8;

Handle<Value> Reference::New(v8::Local<v8::String> args) {

	std::cout << "Calling Reference::New";

	HandleScope scope;
	Reference* obj = new Reference(args);
	obj->Wrap(args.This());
	return scope.Close(args.This());

}

Reference::Reference(const Arguments& args) {

	HandleScope scope;
	// sha_ = V8StringToChar(sha->ToString());

	// git_reference *head_out = args[0];
	std::cout << "Reference constructor called";

};

Handle<Value> Reference::sha(const Arguments& args) {

	HandleScope scope;
	return scope.Close(String::New("the sha string"));
}
