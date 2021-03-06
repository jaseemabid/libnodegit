#include <iostream>

#include <node.h>

#include <git2.h>

#include "util.h"
#include "repository.h"


Handle<Value> Repository::head_(const Arguments& args) {
	 HandleScope scope;
	 Repository* obj = ObjectWrap::Unwrap<Repository>(args.This());

	 git_reference * head_out;

	 int status = git_repository_head(&head_out, obj->repo_);

	 if (status == 0) {
		  const git_oid * head_oid = git_reference_target(head_out);
		  char sha[41]; sha[40] = '\0';

		  git_oid_fmt(sha, head_oid);

		  return scope.Close(String::New(sha));
	 } else {
		  return ThrowException(
			   Exception::Error(
					String::New("Unable to open the git repo")));
	 }
}
