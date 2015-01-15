//#include <errno.h>
//#include <string.h>
#include <nan.h>

#include <iostream>
#include <cstring>

#include "lttng-tp.h"

using namespace v8;

NAN_METHOD(Log) {
  NanScope();
  int level =  args[0].As<Number>()->IntegerValue();
  char* message = *String::Utf8Value(args[1].As<String>());

  // TODO - use switch/case here to call the appropriate tracepoint depending on the bunyan log level passed
  switch(level){
  	case 0:
  		tracepoint(bunyan, emergency, message);
  		break;
  	case 1:
  		tracepoint(bunyan, alert, message);
  		break;
  	case 2:
  		tracepoint(bunyan, critical, message);
  		break;
  	case 3:
  		tracepoint(bunyan, error, message);
  		break;
  	case 4:
  		tracepoint(bunyan, warning, message);
  		break;
  	case 5:
  		tracepoint(bunyan, notice, message);
  		break;
  	case 6:
  		tracepoint(bunyan, info, message);
  		break;
  	case 7:
  		tracepoint(bunyan, debug, message);
  		break;
  }

  NanReturnUndefined();
}

void Init(Handle<Object> exports) {
  exports->Set(NanNew("log"), NanNew<FunctionTemplate>(Log)->GetFunction());
}

NODE_MODULE(lttng, Init);
