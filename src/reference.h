#ifndef REF_H
#define REF_H

#include <node.h>
#include <git2.h>
#include <string>

using namespace v8;

class Reference : public node::ObjectWrap {
public:
	static void Init(v8::Handle<v8::Object> target);

	static v8::Handle<v8::Value> New(const v8::Arguments& args);

	git_reference *head_out;

	std::string sha_;

private:
	Reference(const Arguments& args);
	~Reference();

	static v8::Handle<v8::Value> sha(const v8::Arguments& args);

};

#endif
