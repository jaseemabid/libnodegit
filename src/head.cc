#include <iostream>

#include <node.h>

#include <git2.h>

#include "util.cc"
#include "repository.h"


Handle<Value> Repository::head(const Arguments& args) {
	 HandleScope scope;

	 Repository* obj = ObjectWrap::Unwrap<Repository>(args.This());
	 git_reference * head_out;

	 int status;

	 status = git_repository_head(&head_out, obj->repo_);

	 if (status == 0) {

		  const git_oid * head_oid = git_reference_oid(head_out);

		  char sha[41];
		  sha[40] = '\0';
		  git_oid_fmt(sha, head_oid);

		  //Handle<Reference> head_ref = Reference::New(String::New(sha));

		  return scope.Close(String::New(sha));

	 } else {

		  return ThrowException(Exception::Error(String::New("Unable to open the git repo")));
	 }
}
