#define BUILDING_NODE_EXTENSION

#include <iostream>

#include <node.h>

#include <git2.h>

#include "repository.h"
#include "commit.h"

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

	 git_oid_fromstr(&oid, "361666a55ab643ca9e68de6cc44f800627c002e3");

	 error = git_commit_lookup(&commit, repo, &oid);

	 if (error != 0) {
		  std::cout << "Error looking up commit" ;
	 }

	 msg_string	= git_commit_message(commit);
	 author_sig	= git_commit_author(commit);
	 cmtter_sig	= git_commit_committer(commit);
	 ctime		= git_commit_time(commit);

	// sha_ = V8StringToChar(args[0]->ToString());

	// // Convert std::string to const char* or char*
	// // http://stackoverflow.com/a/347959/501945
	// const char * sha = sha_.c_str();

	// int status;
	// status = git_repository_open(&repo_,c );

	// // Throw an exception for non zero status
	// // TODO This is not working
	// if (status != 0) {
	// 	ThrowException(Exception::Error(v8::String::New("+ Unable to open the git repository")));
	// } else {
	// 	 // Throw is not *throwing*. I need an else clause here
	// 	 git_repository_index(&index_, repo_);
	// 	 git_index_read(index_);
	// }

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
