
#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER bunyan

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./lttng-tp.h"

#if !defined(LTTNG_TP_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define LTTNG_TP_H

#include <lttng/tracepoint.h>

#define MY_TRACEPOINT_ARGS \
    TP_ARGS( \
        char*, msg \
    )

TRACEPOINT_EVENT_CLASS(
    bunyan,
    bunyan_log_levels,
    MY_TRACEPOINT_ARGS,
    TP_FIELDS(
        ctf_string(msg, msg)
    )
)

#define BUNYAN_LOG_LEVEL_TRACEPOINT_INSTANCE(name) \
    TRACEPOINT_EVENT_INSTANCE( \
        bunyan, \
        bunyan_log_levels, \
        name, \
        MY_TRACEPOINT_ARGS \
    )


BUNYAN_LOG_LEVEL_TRACEPOINT_INSTANCE(trace)
BUNYAN_LOG_LEVEL_TRACEPOINT_INSTANCE(debug)
BUNYAN_LOG_LEVEL_TRACEPOINT_INSTANCE(info)
BUNYAN_LOG_LEVEL_TRACEPOINT_INSTANCE(warn)
BUNYAN_LOG_LEVEL_TRACEPOINT_INSTANCE(error)
BUNYAN_LOG_LEVEL_TRACEPOINT_INSTANCE(fatal)


TRACEPOINT_LOGLEVEL(bunyan, trace, TRACE_DEBUG_PROCESS)
TRACEPOINT_LOGLEVEL(bunyan, debug, TRACE_DEBUG)
TRACEPOINT_LOGLEVEL(bunyan, info, TRACE_INFO)
TRACEPOINT_LOGLEVEL(bunyan, warn, TRACE_WARNING)
TRACEPOINT_LOGLEVEL(bunyan, error, TRACE_ERR)
TRACEPOINT_LOGLEVEL(bunyan, fatal, TRACE_EMERG)

/*
TRACEPOINT_EVENT(
    bunyan,
    info,
    TP_ARGS(
        char*, my_string_arg
    ),
    TP_FIELDS(
        ctf_string(my_string_field, my_string_arg)
    )
)
//*/


#endif /* LTTNG_TP_H */

#include <lttng/tracepoint-event.h>
