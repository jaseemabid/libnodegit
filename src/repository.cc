#define BUILDING_NODE_EXTENSION

#include <iostream>

#include <node.h>

#include <git2.h>

#include "util.cpp"
#include "repository.h"

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

Handle<Value> Repository::index(const Arguments& args) {
	HandleScope scope;

	Repository* obj = ObjectWrap::Unwrap<Repository>(args.This());

	git_repository *git_repo;
	git_index *git_index;

	int status;

	unsigned int i, ecount;

	git_oid oid;

	char out[41]; out[40] = '\0';

	// Convert std::string to const char* or char*
	// http://stackoverflow.com/a/347959/501945
	const char * c = obj->path_.c_str();

	status = git_repository_open(&git_repo,c );

	// Throw an exception for non zero status
	if (status != 0) {
		ThrowException(Exception::TypeError(String::New("Unable to open the git repository")));
		return scope.Close(Undefined());
	}

	git_repository_index(&git_index, git_repo);
	git_index_read(git_index);

	ecount = git_index_entrycount(git_index);

	Handle<Array> array = Array::New(ecount);

	for (i = 0; i < ecount; ++i) {

		git_index_entry *e = git_index_get(git_index, i);
		Local<Object> file = Object::New();

		oid = e->oid;
		git_oid_fmt(out, &oid);

		file->Set(String::NewSymbol("path"), String::New(e->path));
		file->Set(String::NewSymbol("sha"), String::New(out));
		file->Set(String::NewSymbol("size"), Integer::New(e->file_size));
		file->Set(String::NewSymbol("device"), Integer::New(e->dev));
		file->Set(String::NewSymbol("inode"), Integer::New(e->ino));
		file->Set(String::NewSymbol("uid"), Integer::New(e->uid));
		file->Set(String::NewSymbol("gid"), Integer::New(e->gid));
		file->Set(String::NewSymbol("ctime"),Integer::New(e->ctime.seconds));
		file->Set(String::NewSymbol("mtime"), Integer::New(e->mtime.seconds));

		array->Set(i, file);
	}

	git_index_free(git_index);
	git_repository_free(git_repo);

	return scope.Close(array);
}
