#include <stdlib.h>
#include <assert.h>

#include "../cfrp.h"
#include "../cfrp_internal.h"
#include "../contrib/cfrp_list.h"

void cfrp_tap_op(EVENT_STREAM *stream, CFRP_NOTIFICATION *notification);

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

void cfrp_tap_op(EVENT_STREAM *stream, CFRP_NOTIFICATION *notification)
{
  stream->op_arg(notification->value);
}
