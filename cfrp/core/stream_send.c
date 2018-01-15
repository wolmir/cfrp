#include <stdlib.h>

#include "../cfrp.h"
#include "../cfrp_internal.h"
#include "../contrib/cfrp_list.h"
#include "../contrib/cfrp_queue.h"

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
