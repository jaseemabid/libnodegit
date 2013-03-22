#include <node.h>
#include <v8.h>

#include "util.h"
#include "repository.h"

#include <git2.h>

#include <iostream>

using namespace v8;
using namespace std;

Handle<Value> Repository::index(const Arguments& args) {
	HandleScope scope;

	Repository* obj = ObjectWrap::Unwrap<Repository>(args.This());

	unsigned int i, index_size;
	git_oid oid;
	char out[41]; out[40] = '\0';

	index_size = git_index_entrycount(obj->index_);
	Handle<Array> array = Array::New(index_size);

	for (i = 0; i < index_size; i++) {

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

	return scope.Close(array);
}
