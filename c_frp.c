#include <stdlib.h>

#include "c_frp.h"
#include "cfrp_list.h"
#include "cfrp_queue.h"

EVENT_STREAM *cfrp_create_event_stream()
{
  EVENT_STREAM *stream = NULL;

  stream = malloc(sizeof(EVENT_STREAM));

  stream->status = CFRP_UNTAPPED;
  stream->subscribers = cfrp_create_list();
  stream->sources = cfrp_create_list();

  stream->value_queue = cfrp_create_queue();

  stream->op_type = CFRP_SINK;

  return stream;
}

CFRP_ERROR_ENUM cfrp_stream_send(EVENT_STREAM *stream, void *value)
{
  if (stream == NULL) {
    return CFRP_INVALID_STREAM;
  }

  if (stream->status == CFRP_UNTAPPED) {
    cfrp_enqueue(stream->value_queue, value);

    return CFRP_NO_SUBSCRIBERS;
  }

  cfrp_list_foreach(stream->subscribers, cfrp_notify, value);

  return CFRP_NO_ERROR;
}

EVENT_STREAM *cfrp_stream_tap(EVENT_STREAM *source, void* (*listener) (void *value))
{
  if (source == NULL) {
    return NULL;
  }

  if (listener == NULL) {
    return NULL;
  }

  EVENT_STREAM *tap_stream = cfrp_create_event_stream();

  tap_stream->op_type = CFRP_TAP;
  tap_stream->op_func = listener;

  cfrp_list_append(source->subscribers, tap_stream);
  cfrp_list_append(tap_stream->sources, source);

  cfrp_notify_tap(source, NULL);

  return tap_stream;
}

void cfrp_notify(void *stream, void *value)
{
  EVENT_STREAM *_stream = (EVENT_STREAM*)stream;

  void* new_value = _stream->op_func(value);

  cfrp_list_foreach(_stream->subscribers, cfrp_notify, new_value);
}

void cfrp_notify_tap(void *_stream, void *arg)
{
  EVENT_STREAM *stream = (EVENT_STREAM*)_stream;

  if (stream->status == CFRP_UNTAPPED) {
    stream->status = CFRP_TAPPED;
    cfrp_list_foreach(stream->sources, cfrp_notify_tap, NULL);

    while (!cfrp_queue_is_empty(stream->value_queue)) {
      void *value = cfrp_dequeue(stream->value_queue);

      cfrp_list_foreach(stream->subscribers, cfrp_notify, value);
    }
  }
}
