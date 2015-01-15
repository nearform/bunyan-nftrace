//#include <errno.h>
//#include <string.h>
#include <nan.h>

#include <iostream>
#include <cstring>

#include "lttng-tp.h"

using namespace v8;

NAN_METHOD(Log) {
  NanScope();
  //int level =  args[0].As<Number>()->IntegerValue();
  char* message = *String::Utf8Value(args[1].As<String>());

  // TODO - use switch/case here to call the appropriate tracepoint depending on the bunyan log level passed
  tracepoint(bunyan, info, message);

  NanReturnUndefined();
}

void Init(Handle<Object> exports) {
  exports->Set(NanNew("log"), NanNew<FunctionTemplate>(Log)->GetFunction());
}

NODE_MODULE(lttng, Init);
