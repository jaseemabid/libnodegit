#include <iostream>

#include <node.h>

#include <git2.h>

#include "util.cc"
#include "repository.h"
#include "index.cc"
#include "head.cc"


using namespace v8;

Repository::Repository(const Arguments& args) {

	path_ = V8StringToChar(args[0]->ToString());

	// Convert std::string to const char* or char*
	// http://stackoverflow.com/a/347959/501945
	const char * c = path_.c_str();

	int status;
	status = git_repository_open(&repo_,c );

	// Throw an exception for non zero status
	// TODO This is not working
	if (status != 0) {
		ThrowException(Exception::Error(v8::String::New("+ Unable to open the git repository")));
	}

	git_repository_index(&index_, repo_);
	git_index_read(index_);
};

Repository::~Repository() {

	// TODO Unsure if this will GC properly
	git_index_free(index_);
	git_repository_free(repo_);

};

void Repository::Init(Handle<Object> target) {

	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->SetClassName(String::NewSymbol("Repository"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	tpl->PrototypeTemplate()->Set(String::NewSymbol("index"),
								  FunctionTemplate::New(index)->GetFunction());

	tpl->PrototypeTemplate()->Set(String::NewSymbol("isEmpty"),
								  FunctionTemplate::New(isEmpty)->GetFunction());

	tpl->PrototypeTemplate()->Set(String::NewSymbol("isBare"),
								  FunctionTemplate::New(isBare)->GetFunction());

	tpl->PrototypeTemplate()->Set(String::NewSymbol("head"),
								  FunctionTemplate::New(head)->GetFunction());

	Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
	target->Set(String::NewSymbol("Repository"), constructor);
}

Handle<Value> Repository::New(const Arguments& args) {

	HandleScope scope;
	Repository* obj = new Repository(args);
	obj->Wrap(args.This());
	return scope.Close(args.This());

}

Handle<Value> Repository::isEmpty(const Arguments& args) {

	HandleScope scope;
	Repository* obj = ObjectWrap::Unwrap<Repository>(args.This());

	int isEmpty;
	isEmpty =  git_repository_is_empty(obj->repo_);

	if(isEmpty == 1)  {
		return scope.Close(v8::True());
	} else {
		return scope.Close(v8::False());
	}
}

Handle<Value> Repository::isBare(const Arguments& args) {

	HandleScope scope;
	Repository* obj = ObjectWrap::Unwrap<Repository>(args.This());

	int isBare;
	isBare =  git_repository_is_bare(obj->repo_);

	if(isBare == 1)  {
		return scope.Close(v8::True());
	} else {
		return scope.Close(v8::False());
	}
}
