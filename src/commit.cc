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

	Persistent<Function> constructor = Persistent<Function>::New(tpl->GetFunction());
	target->Set(String::NewSymbol("Commit"), constructor);
}

Commit::Commit(const Arguments& args) {
	 /*
	   Initialize a commit object with a SHA
	  */

	 if(args.Length() == 0 || !args[0]->IsString()) {
		  ThrowException(
			   Exception::Error(
					String::New("SHA id is required and must be a String")));
	 }

	 int error;
	 git_repository *repo;

	 error = git_repository_open(&repo, "/home/jaseemabid/Projects/libnodegit");

	 /* Get the sha id in a format v8 understands
	   Convert std::string to const char* or char*
	   http://stackoverflow.com/a/347959/501945 */

	 sha_ = V8StringToChar(args[0]->ToString());
	 const char * sha = sha_.c_str();

	 git_oid_fromstr(&oid, sha);

	 error = git_commit_lookup(&commit, repo, &oid);

	 if (error != 0) {
		  ThrowException(
			   Exception::Error(
					String::New("Error looking up the commit")));
	 }


	 // Read commit values and store to class variables
	 msg_string	= git_commit_message(commit);
	 author_sig	= git_commit_author(commit);
	 cmtter_sig	= git_commit_committer(commit);
	 ctime		= git_commit_time(commit);

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
