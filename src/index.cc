#include <node.h>
#include <v8.h>

#include <git2.h>

#include <iostream>

using namespace v8;
using namespace std;


Handle<Value> index(const Arguments& args) {

	 HandleScope scope;

	 /*
		libgit2 variables

		Will have to move this to a common header with a nodelibgit namespace or
		something
	 */

	 git_repository *git_repo;
	 git_index *git_index;

	 int status;

	 unsigned int i, ecount;

	 git_oid oid;

	 char out[41]; out[40] = '\0';

	 status = git_repository_open(&git_repo, "/home/jaseem/Projects/libnodegit" ); // Use argv[0]

	 cout << "Repo st " << status << endl; // Throw an exception for non zero

	 git_repository_index(&git_index, git_repo);
	 git_index_read(git_index);

	 ecount = git_index_entrycount(git_index);

	 cout << "count : " << ecount << endl;

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

Handle<Value> foo(const Arguments& args) {
	 HandleScope scope;

	 Local<Integer> integer = args[0]->ToInteger();
	 int32_t seq = integer->Value();
	 return scope.Close(Integer::New(seq));
}

void init(Handle<Object> target) {

	 NODE_SET_METHOD(target, "index", index);
	 NODE_SET_METHOD(target, "foo", foo);
}


NODE_MODULE(libnodegit, init)
