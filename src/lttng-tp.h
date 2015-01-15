
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


BUNYAN_LOG_LEVEL_TRACEPOINT_INSTANCE(emergency)
BUNYAN_LOG_LEVEL_TRACEPOINT_INSTANCE(alert)
BUNYAN_LOG_LEVEL_TRACEPOINT_INSTANCE(critical)
BUNYAN_LOG_LEVEL_TRACEPOINT_INSTANCE(error)
BUNYAN_LOG_LEVEL_TRACEPOINT_INSTANCE(warning)
BUNYAN_LOG_LEVEL_TRACEPOINT_INSTANCE(notice)
BUNYAN_LOG_LEVEL_TRACEPOINT_INSTANCE(info)
BUNYAN_LOG_LEVEL_TRACEPOINT_INSTANCE(debug)
//BUNYAN_LOG_LEVEL_TRACEPOINT_INSTANCE(trace)


TRACEPOINT_LOGLEVEL(bunyan, emergency, TRACE_EMERG)
TRACEPOINT_LOGLEVEL(bunyan, alert, TRACE_ALERT)
TRACEPOINT_LOGLEVEL(bunyan, critical, TRACE_CRIT)
TRACEPOINT_LOGLEVEL(bunyan, error, TRACE_ERR)
TRACEPOINT_LOGLEVEL(bunyan, warning, TRACE_WARNING)
TRACEPOINT_LOGLEVEL(bunyan, info, TRACE_INFO)
TRACEPOINT_LOGLEVEL(bunyan, debug, TRACE_DEBUG)
//TRACEPOINT_LOGLEVEL(bunyan, trace, TRACE_TRACE)

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
