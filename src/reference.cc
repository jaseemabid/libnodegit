#include <iostream>

#include <node.h>

#include <git2.h>

#include "util.cc"
#include "reference.h"
#include "index.cc"
#include "head.cc"


using namespace v8;

Reference::Reference(const Arguments& args) {

	HandleScope scope;
	// sha_ = V8StringToChar(sha->ToString());

	// git_reference *head_out = args[0];
	std::cout << "Reference constructor called";

};

void Reference::Init(Handle<Object> target) {

	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->SetClassName(String::NewSymbol("Reference"));
	tpl->InstanceTemplate()->SetInternalFieldCount(2);

	// Prototype
	tpl->PrototypeTemplate()->Set(String::NewSymbol("sha"),
								  FunctionTemplate::New(sha)->GetFunction());

	Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
	target->Set(String::NewSymbol("Reference"), constructor);
}

Handle<Value> Reference::New(const Arguments& args) {

	HandleScope scope;
	Reference* obj = new Reference(args);
	obj->Wrap(args.This());
	return scope.Close(args.This());

}


Handle<Value> Reference::sha(const Arguments& args) {

	HandleScope scope;
	return scope.Close(String::New("the sha string"));
}
