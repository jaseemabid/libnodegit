#define BUILDING_NODE_EXTENSION

#include <node.h>
#include "repository.h"

using namespace v8;

void InitAll(Handle<Object> target) {
  Repository::Init(target);
}

NODE_MODULE(libnodegit, InitAll)
