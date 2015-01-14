//#include <errno.h>
//#include <string.h>
#include <iostream>
#include <node.h>
#include <v8.h>
#include "lttng-tp.h"

using namespace v8;

#define RETURN_EXCEPTION(MSG)                                           \
	return ThrowException(Exception::Error(String::New(MSG)))

#define RETURN_ARGS_EXCEPTION(MSG)                                      \
	return ThrowException(Exception::TypeError(String::New(MSG)))

#define RETURN_ERRNO_EXCEPTION(RC, API, MSG)				\
	return ThrowException(node::ErrnoException(RC, API, MSG))

#define RETURN_OOM_EXCEPTION()						\
	RETURN_ERRNO_EXCEPTION(ENOMEM, "malloc", strerror(ENOMEM))

#define REQUIRE_ARGS(ARGS)					\
	if (ARGS.Length() == 0)					\
		RETURN_ARGS_EXCEPTION("missing arguments");

#define REQUIRE_INT_ARG(ARGS, I, VAR)                                   \
	REQUIRE_ARGS(ARGS);						\
	if (ARGS.Length() <= (I) || !ARGS[I]->IsNumber())		\
		RETURN_ARGS_EXCEPTION("argument " #I " must be an Integer"); \
	Local<Integer> _ ## VAR(ARGS[I]->ToInteger());			\
	int VAR = _ ## VAR->Value();

#define REQUIRE_STRING_ARG(ARGS, I, VAR)				\
	REQUIRE_ARGS(ARGS);						\
	if (ARGS.Length() <= (I) || !ARGS[I]->IsString())		\
		RETURN_ARGS_EXCEPTION("argument " #I " must be a String"); \
	String::Utf8Value VAR(ARGS[I]->ToString());

#define REQUIRE_FUNCTION_ARG(ARGS, I, VAR)                              \
	REQUIRE_ARGS(ARGS);						\
	if (ARGS.Length() <= (I) || !ARGS[I]->IsFunction())		\
		RETURN_EXCEPTION("argument " #I " must be a Function");	\
	Local<Function> VAR = Local<Function>::Cast(ARGS[I]);


#define REQUIRE_OBJECT_ARG(ARGS, I, VAR)				\
	REQUIRE_ARGS(ARGS);						\
	if (ARGS.Length() <= (I) || !ARGS[I]->IsObject())		\
		RETURN_EXCEPTION("argument " #I " must be an Object");	\
	Local<Object> VAR(ARGS[I]->ToObject());



///--- API


Handle<Value> Log(const Arguments& args) {
	HandleScope scope;

	REQUIRE_INT_ARG(args, 0, level);
	REQUIRE_STRING_ARG(args, 1, message);

  //std::cout << "** in native, got message: " << *message << std::endl;

  // TODO - use switch/case here to call the appropriate tracepoint depending on the bunyan log level passed
  tracepoint(bunyan, info, *message);

	return (Undefined());
}

void init(Handle<Object> target) {
	NODE_SET_METHOD(target, "log", Log);
}

NODE_MODULE(lttng, init);
