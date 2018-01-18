#include <stdlib.h>
#include <assert.h>

#include "../cfrp.h"
#include "../cfrp_internal.h"
#include "../contrib/cfrp_list.h"

void cfrp_filter_op(EVENT_STREAM *stream, CFRP_NOTIFICATION *notification);

EVENT_STREAM *cfrp_stream_filter(EVENT_STREAM *source, void* (*func) (void *value))
{
  assert(source != NULL);
  assert(func != NULL);

  EVENT_STREAM *filter_stream = cfrp_create_event_stream();

  filter_stream->op_type = CFRP_FILTER;
  filter_stream->op_func = cfrp_filter_op;
  filter_stream->op_arg = func;

  cfrp_list_append(source->subscribers, filter_stream);
  cfrp_list_append(filter_stream->sources, source);

  return filter_stream;
}

void cfrp_filter_op(EVENT_STREAM *stream, CFRP_NOTIFICATION *notification)
{
  void *result = stream->op_arg(notification->value);

  if (result != NULL) {
    cfrp_list_foreach(stream->subscribers, cfrp_notify, notification);
  }
}