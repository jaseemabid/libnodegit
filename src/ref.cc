#include <node.h>
#include <v8.h>

#include "util.cc"
#include "repository.h"

#include <git2.h>

#include <iostream>

using namespace v8;

Handle<Value> Repository::head(const Arguments& args) {
	HandleScope scope;

	Repository* obj = ObjectWrap::Unwrap<Repository>(args.This());
	git_reference * head_out;

	int status;

	status = git_repository_head(&head_out, obj->repo_);

	if (status == 0) {

		const git_oid * head_oid = git_reference_oid(head_out);

		char out[41];
		out[40] = '\0';
		git_oid_fmt(out, head_oid);

		return scope.Close(String::New(out));

	} else {

		return ThrowException(Exception::Error(String::New("Unable to open the git repo")));
	}
}
