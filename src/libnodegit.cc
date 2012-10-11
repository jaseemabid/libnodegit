#define BUILDING_NODE_EXTENSION

#include <node.h>
#include "repository.h"
#include "reference.h"

using namespace v8;

void InitAll(Handle<Object> target) {
  Repository::Init(target);
  Reference::Init(target);
}

NODE_MODULE(libnodegit, InitAll)
