#include <stdlib.h>
#include <assert.h>

#include "../cfrp.h"
#include "../cfrp_internal.h"
#include "../contrib/cfrp_list.h"

void cfrp_merge_op(EVENT_STREAM *stream, CFRP_NOTIFICATION *notification);

EVENT_STREAM *cfrp_stream_merge(EVENT_STREAM **sources, int num_streams)
{
  assert(sources != NULL);

  EVENT_STREAM *merge_stream = cfrp_create_event_stream();

  merge_stream->op_type = CFRP_MERGE;
  merge_stream->op_func = cfrp_merge_op;

  int i;

  for (i = 0; i < num_streams; i++) {
    cfrp_list_append(sources[i]->subscribers, merge_stream);
    cfrp_list_append(merge_stream->sources, sources[i]);
  }

  return merge_stream;
}

void cfrp_merge_op(EVENT_STREAM *stream, CFRP_NOTIFICATION *notification)
{
  cfrp_list_foreach(stream->subscribers, cfrp_notify, notification);
}