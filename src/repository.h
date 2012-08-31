#ifndef REPOSITORY_H
#define REPOSITORY_H

#include <node.h>
#include <string>

using namespace v8;

class Repository : public node::ObjectWrap {
public:
	static void Init(v8::Handle<v8::Object> target);

private:
	Repository();
	~Repository();

	static v8::Handle<v8::Value> New(const v8::Arguments& args);
	static v8::Handle<v8::Value> index(const v8::Arguments& args);
	std::string path_;
};

#endif
