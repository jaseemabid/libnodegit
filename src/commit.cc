#include <iostream>

#include <node.h>

#include <git2.h>

#include "repository.h"
#include "commit.h"

#include "util.h"

using namespace v8;

void Commit::Initialize(Handle<Object> target) {

	// Prepare constructor template
	Local<FunctionTemplate> tpl = FunctionTemplate::New(New);
	tpl->SetClassName(String::NewSymbol("Commit"));
	tpl->InstanceTemplate()->SetInternalFieldCount(1);

	// Prototype
	tpl->PrototypeTemplate()->Set(String::NewSymbol("message"),
								  FunctionTemplate::New(message)->GetFunction());

	tpl->PrototypeTemplate()->Set(String::NewSymbol("parents"),
								  FunctionTemplate::New(parents)->GetFunction());

	Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
	target->Set(String::NewSymbol("Commit"), constructor);
}

Commit::Commit(const Arguments& args) {
	 /*
	   Initialize a commit object with a SHA
	  */

	 // Can't just return from a C++ constructor on error? WTF!
	 // Ideally I'd just return, but looks like I need a error bit here.
	 int error = 0;

	 if(args.Length() < 2 || !args[0]->IsString()) {
		  ThrowException(
			   Exception::Error(
					String::New("SHA id is required and must be a String")));

		  error = 1;
	 }

	 if(args.Length() < 2 || !args[1]->IsString()) {
		  ThrowException(
			   Exception::Error(
					String::New("Path is required and must be a String")));

		  error = 1;
	 }

	 git_repository *repo;

	 if (!error) {
		  std::string path_ = V8StringToChar(args[1]->ToString());
		  const char * path = path_.c_str();

		  error = git_repository_open(&repo, path);
	 }

	 if (!error) {
		  /* Get the sha id in a format v8 understands
			 Convert std::string to const char* or char*
			 http://stackoverflow.com/a/347959/501945 */

		  sha_ = V8StringToChar(args[0]->ToString());
		  const char * sha = sha_.c_str();

		  git_oid_fromstr(&oid, sha);

		  error = git_commit_lookup(&commit, repo, &oid);
	 }

	 if (error != 0) {
		  ThrowException(
			   Exception::Error(
					String::New("Error looking up the commit")));
	 }

	 if(! error) {

		  // Read commit values and store to class variables
		  msg_string	= git_commit_message(commit);
		  author_sig	= git_commit_author(commit);
		  cmtter_sig	= git_commit_committer(commit);
		  ctime		= git_commit_time(commit);
	 }

};

Commit::~Commit() {

	 // TODO Unsure if this will GC properly
	 // Do I really need to do this?
};

Handle<Value> Commit::New(const Arguments& args) {

	HandleScope scope;
	Commit* obj = new Commit(args);
	obj->Wrap(args.This());
	return scope.Close(args.This());

}


Handle<Value> Commit::message(const Arguments& args) {

	 HandleScope scope;

	 Commit* obj = ObjectWrap::Unwrap<Commit>(args.This());

	 if(obj) {
		  return scope.Close(String::New(obj->msg_string));

	 } else {
		  return ThrowException(
			   Exception::Error(
					String::New("Unable to get the commit")));
	 }
}

Handle<Value> Commit::parents(const Arguments& args) {
	 HandleScope scope;
	 Commit* obj = ObjectWrap::Unwrap<Commit>(args.This());

	 unsigned int parent_count, p;
	 char out[41]; out[40] = '\0';

	 parent_count = git_commit_parentcount(obj->commit);

	 Handle<v8::Array> parents = v8::Array::New(2);

	 for (p = 0;p < parent_count;p++) {
		  git_commit *parent;
		  git_commit_parent(&parent, obj->commit, p);
		  git_oid_fmt(out, git_commit_id(parent));
		  parents->Set(p, v8::String::New(out));
		  git_commit_free(parent);
	 }

	 return scope.Close(parents);
}
