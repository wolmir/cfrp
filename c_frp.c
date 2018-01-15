#include <stdlib.h>
#include <assert.h>

#include "c_frp.h"
#include "cfrp_list.h"
#include "cfrp_queue.h"

void cfrp_notify(void *_stream, void *value);
void cfrp_notify_tap(void *_stream, void *arg); // The last argument is merely for the foreach compatibility
void cfrp_update_old_value(EVENT_STREAM *stream, void *value);

void cfrp_tap_op(EVENT_STREAM *stream, void *value);
void cfrp_map_op(EVENT_STREAM *stream, void *value);

EVENT_STREAM *cfrp_create_event_stream()
{
  EVENT_STREAM *stream = NULL;

  stream = malloc(sizeof(EVENT_STREAM));

  stream->status = CFRP_UNTAPPED;
  stream->subscribers = cfrp_create_list();
  stream->sources = cfrp_create_list();

  stream->old_value = NULL;

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
  assert(source != NULL);
  assert(listener != NULL);

  EVENT_STREAM *tap_stream = cfrp_create_event_stream();

  tap_stream->op_type = CFRP_TAP;
  tap_stream->op_func = cfrp_tap_op;
  tap_stream->op_arg = listener;

  cfrp_list_append(source->subscribers, tap_stream);
  cfrp_list_append(tap_stream->sources, source);

  cfrp_notify_tap(source, NULL);

  return tap_stream;
}

EVENT_STREAM *cfrp_stream_map(EVENT_STREAM *source, void* (*func) (void *value))
{
  assert(source != NULL);
  assert(func != NULL);

  EVENT_STREAM *map_stream = cfrp_create_event_stream();

  map_stream->op_type = CFRP_MAP;
  map_stream->op_func = cfrp_map_op;
  map_stream->op_arg = func;

  cfrp_list_append(source->subscribers, map_stream);
  cfrp_list_append(map_stream->sources, source);

  return map_stream;
}

void cfrp_notify(void *_stream, void *value)
{
  EVENT_STREAM *stream = (EVENT_STREAM*)_stream;

  stream->op_func(stream, value);

  // cfrp_list_foreach(_stream->subscribers, cfrp_notify, new_value);
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

void cfrp_update_old_value(EVENT_STREAM *stream, void *value) {
  if (stream->old_value != NULL) {
    free(stream->old_value);
  }

  stream->old_value = value;
}

void cfrp_tap_op(EVENT_STREAM *stream, void *value)
{
  stream->op_arg(value);
}

void cfrp_map_op(EVENT_STREAM *stream, void *value)
{
  void *new_value = stream->op_arg(value);

  cfrp_update_old_value(stream, new_value);

  cfrp_list_foreach(stream->subscribers, cfrp_notify, new_value);
}
