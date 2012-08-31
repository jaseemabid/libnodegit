#define BUILDING_NODE_EXTENSION

#include <iostream>

#include <node.h>

#include <git2.h>

#include "util.cpp"
#include "repository.h"

#include "index.cc"

using namespace v8;

Repository::Repository() {};
Repository::~Repository() {};

void Repository::Init(Handle<Object> target) {

	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->SetClassName(String::NewSymbol("Repository"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	tpl->PrototypeTemplate()->Set(String::NewSymbol("index"),
								  FunctionTemplate::New(index)->GetFunction());

	Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
	target->Set(String::NewSymbol("Repository"), constructor);
}

Handle<Value> Repository::New(const Arguments& args) {
	HandleScope scope;
	Repository* obj = new Repository();

	obj->path_ = V8StringToChar(args[0]->ToString());

	obj->Wrap(args.This());
	return args.This();
}
