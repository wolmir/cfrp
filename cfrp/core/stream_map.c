#include <stdlib.h>
#include <assert.h>

#include "../cfrp.h"
#include "../cfrp_internal.h"
#include "../contrib/cfrp_list.h"

void cfrp_map_op(EVENT_STREAM *stream, CFRP_NOTIFICATION *notification);

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

void cfrp_map_op(EVENT_STREAM *stream, CFRP_NOTIFICATION *notification)
{
  void *new_value = stream->op_arg(notification->value);

  CFRP_NOTIFICATION *new_notification = (CFRP_NOTIFICATION*)malloc(sizeof(CFRP_NOTIFICATION));
  new_notification->value = new_value;

  cfrp_list_foreach(stream->subscribers, cfrp_notify, new_notification);

  free(new_notification);
}