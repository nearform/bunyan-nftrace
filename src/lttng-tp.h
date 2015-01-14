
#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER bunyan

#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "./lttng-tp.h"

#if !defined(LTTNG_TP_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define LTTNG_TP_H

#include <lttng/tracepoint.h>

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

TRACEPOINT_LOGLEVEL(bunyan, info, TRACE_INFO)

#endif /* LTTNG_TP_H */

#include <lttng/tracepoint-event.h>
