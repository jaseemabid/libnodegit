#include <node.h>

#include "repository.h"
#include "commit.h"


using namespace v8;

void InitAll(Handle<Object> target) {
  Repository::Initialize(target);
  Commit::Initialize(target);
}

NODE_MODULE(libnodegit, InitAll)
