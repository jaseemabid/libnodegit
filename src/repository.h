#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <node.h>
#include <git2.h>
#include <string>

using namespace v8;

class Repository : public node::ObjectWrap {
public:
	static void Init(v8::Handle<v8::Object> target);

	git_repository *repo_;
	git_index *index_;

	std::string path_;

private:
	Repository(const Arguments& args);
	~Repository();

	static v8::Handle<v8::Value> New(const v8::Arguments& args);
	static v8::Handle<v8::Value> index(const v8::Arguments& args);
	static v8::Handle<v8::Value> isBare(const v8::Arguments& args);
	static v8::Handle<v8::Value> isEmpty(const v8::Arguments& args);
	static v8::Handle<v8::Value> head(const v8::Arguments& args);

};

#endif
