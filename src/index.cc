#include <node.h>
#include <v8.h>

#include "util.cc"
#include "repository.h"

#include <git2.h>

#include <iostream>

using namespace v8;
using namespace std;

Handle<Value> Repository::index(const Arguments& args) {
	HandleScope scope;

	Repository* obj = ObjectWrap::Unwrap<Repository>(args.This());

	int status;
	unsigned int i, ecount;

	git_oid oid;

	char out[41]; out[40] = '\0';

	// Convert std::string to const char* or char*
	// http://stackoverflow.com/a/347959/501945
	const char * c = obj->path_.c_str();

	status = git_repository_open(&(obj->repo_),c );

	// Throw an exception for non zero status
	// TODO: This is not working
	if (status != 0) {
		ThrowException(Exception::Error(v8::String::New("+ Unable to open the git repository")));
		return scope.Close(Undefined());
	}

	git_repository_index(&(obj->index_), obj->repo_);
	git_index_read(obj->index_);

	ecount = git_index_entrycount(obj->index_);

	Handle<Array> array = Array::New(ecount);

	for (i = 0; i < ecount; ++i) {

		git_index_entry *e = git_index_get(obj->index_, i);
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

	git_index_free(obj->index_);
	git_repository_free(obj->repo_);

	return scope.Close(array);
}
