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
  char *message = (char *) malloc(string.length() + 1);
  strcpy(message, *string);
  
  switch(level){
  	case 10:
  		tracepoint(bunyan, trace, message);
  		break;
  	case 20:
  		tracepoint(bunyan, debug, message);
  		break;
  	case 30:
  		tracepoint(bunyan, info, message);
  		break;
  	case 40:
  		tracepoint(bunyan, warn, message);
  		break;
  	case 50:
  		tracepoint(bunyan, error, message);
  		break;
  	case 60:
  		tracepoint(bunyan, fatal, message);
  		break;
  }

  NanReturnUndefined();
}

char* get(Local<Value> value, const char *fallback = "") {
    if (value->IsString()) {
        String::AsciiValue string(value);
        char *str = (char *) malloc(string.length() + 1);
        strcpy(str, *string);
        return str;
    }
    char *str = (char *) malloc(strlen(fallback) + 1);
    strcpy(str, fallback);
    return str;
}

void Init(Handle<Object> exports) {
  exports->Set(NanNew("log"), NanNew<FunctionTemplate>(Log)->GetFunction());
}

NODE_MODULE(lttng, Init);
