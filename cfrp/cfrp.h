#ifndef C_FRP
#define C_FRP

#include "contrib/cfrp_list.h"
#include "contrib/cfrp_queue.h"

#define cfrp_bool(E) (E) ? (void*)1 : NULL // Used in places that check for NULL values, like filter.

typedef enum {
  CFRP_NO_ERROR,
  CFRP_INVALID_STREAM,
  CFRP_NO_SUBSCRIBERS
} CFRP_ERROR_ENUM;

typedef enum {
  CFRP_SINK,
  CFRP_TAP,
  CFRP_MAP,
  CFRP_FILTER
} CFRP_OP_TYPE;

typedef enum {
  CFRP_TAPPED,
  CFRP_UNTAPPED
} CFRP_STATUS;

typedef struct EVENT_STREAM EVENT_STREAM;
struct EVENT_STREAM {
  void (*op_func) (EVENT_STREAM *stream, void *value); // The stream op function.
  void* (*op_arg) (void *value); // The supplied function of many ops.
  void *old_value; // Used for memory management;
  CFRP_STATUS status;
  CFRP_OP_TYPE op_type; // This might be useful later.
  CFRP_QUEUE *value_queue;
  CFRP_LIST *sources;
  CFRP_LIST *subscribers;
};

EVENT_STREAM *cfrp_create_event_stream();

CFRP_ERROR_ENUM cfrp_stream_send(EVENT_STREAM *stream, void *value);

EVENT_STREAM *cfrp_stream_tap(EVENT_STREAM *stream, void* (*listener) (void *value));

EVENT_STREAM *cfrp_stream_map(EVENT_STREAM *stream, void* (*func) (void *value));

EVENT_STREAM *cfrp_stream_filter(EVENT_STREAM *stream, void* (*func) (void *value));

#endif
