#include <node.h>
#include <v8.h>

#include "util.cpp"

#include <git2.h>

#include <iostream>

using namespace v8;
using namespace std;

Handle<Value> gitIndex(const Arguments& args) {

	 HandleScope scope;

	 /*
	   libgit2 variables

	   Will have to move this to a common header with a nodelibgit namespace or
	   something
	 */

	 if (args.Length() < 1) {
		  ThrowException(Exception::TypeError(String::New("Argument missing")));
		  return scope.Close(Undefined());
	 }

	 if (!args[0]->IsString()) {
		  ThrowException(Exception::TypeError(String::New("Argument should be a path string")));
		  return scope.Close(Undefined());
	 }

	 git_repository *git_repo;
	 git_index *git_index;

	 int status;

	 unsigned int i, ecount;

	 git_oid oid;

	 char out[41]; out[40] = '\0';

	 status = git_repository_open(&git_repo, V8StringToChar(args[0]->ToString()));

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

Handle<Value> Repository(const Arguments& args) {
	 HandleScope scope;

	 Local<Object> obj = Object::New();
	 obj->Set(String::NewSymbol("path"), args[0]->ToString());

	 NODE_SET_METHOD(obj, "index", gitIndex);

	 return scope.Close(obj);
}



void init(Handle<Object> target) {

	 target->Set(String::NewSymbol("Repository"),
				 FunctionTemplate::New(Repository)->GetFunction());
}

NODE_MODULE(libnodegit, init)
