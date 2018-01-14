#ifndef C_FRP
#define C_FRP

#include "cfrp_list.h"
#include "cfrp_queue.h"

typedef enum {
  CFRP_NO_ERROR,
  CFRP_INVALID_STREAM,
  CFRP_NO_SUBSCRIBERS
} CFRP_ERROR_ENUM;

typedef enum {
  CFRP_SINK,
  CFRP_TAP
} CFRP_OP_TYPE;

typedef enum {
  CFRP_TAPPED,
  CFRP_UNTAPPED
} CFRP_STATUS;

typedef struct EVENT_STREAM EVENT_STREAM;
struct EVENT_STREAM {
  void* (*op_func) (void *value); // The stream op function
  CFRP_STATUS status;
  CFRP_OP_TYPE op_type;
  CFRP_QUEUE *value_queue;
  CFRP_LIST *sources;
  CFRP_LIST *subscribers;
};

EVENT_STREAM *cfrp_create_event_stream();

CFRP_ERROR_ENUM cfrp_stream_send(EVENT_STREAM *stream, void *value);

EVENT_STREAM *cfrp_stream_tap(EVENT_STREAM *stream, void* (*listener) (void *value));

void cfrp_notify(void *stream, void *value);

void cfrp_notify_tap(void *_stream, void *arg); // The last argument is merely for the foreach compatibility

#endif
