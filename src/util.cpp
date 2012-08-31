#include <v8.h>

using namespace v8;

char* V8StringToChar(Handle<String> str) {
  int len = str->Utf8Length();
  char* buf = new char[len + 1];
  str->WriteUtf8(buf, len + 1);
  return buf;
}

char* V8StringToChar(Local<Value> val) {
  return V8StringToChar(val->ToString());
}
