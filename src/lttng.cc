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
  
  String::AsciiValue string(args[1]);
  
  switch(level){
  	case 10:
  		tracepoint(bunyan, trace, *string);
  		break;
  	case 20:
  		tracepoint(bunyan, debug, *string);
  		break;
  	case 30:
  		tracepoint(bunyan, info, *string);
  		break;
  	case 40:
  		tracepoint(bunyan, warn, *string);
  		break;
  	case 50:
  		tracepoint(bunyan, error, *string);
  		break;
  	case 60:
  		tracepoint(bunyan, fatal, *string);
  		break;
  }

  NanReturnUndefined();
}

void Init(Handle<Object> exports) {
  exports->Set(NanNew("log"), NanNew<FunctionTemplate>(Log)->GetFunction());
}

NODE_MODULE(lttng, Init);
