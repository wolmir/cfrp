#include <stdlib.h>

#include "cfrp.h"
#include "cfrp_internal.h"
#include "contrib/cfrp_list.h"
#include "contrib/cfrp_queue.h"

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

void cfrp_notify(void *_stream, void *value)
{
  EVENT_STREAM *stream = (EVENT_STREAM*)_stream;

  stream->op_func(stream, value);
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
