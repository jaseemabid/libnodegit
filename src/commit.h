#ifndef COMMIT_H
#define COMMIT_H

#include <node.h>
#include <git2.h>
#include <string>

using namespace v8;

class Commit : public node::ObjectWrap {
public:
	static void Initialize(v8::Handle<v8::Object> target);

	/*
	   Public properties of the commit object
	 */
	git_commit *commit;
	git_oid oid;

	const git_signature *author_sig, *cmtter_sig;
	const char *msg_string;
	time_t ctime;

	std::string sha_;

private:
	Commit(const Arguments& args);
	~Commit();

	static v8::Handle<v8::Value> New(const v8::Arguments& args);
	static v8::Handle<v8::Value> message(const v8::Arguments& args);
	static v8::Handle<v8::Value> parents_(const v8::Arguments& args);

};

#endif
