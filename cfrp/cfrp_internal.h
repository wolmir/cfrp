#ifndef CFRP_INTERNAL_H
#define CFRP_INTERNAL_H

#include "cfrp.h"

void cfrp_notify(void *_stream, void *value);
void cfrp_notify_tap(void *_stream, void *arg); // The last argument is merely for the foreach compatibility
void cfrp_update_old_value(EVENT_STREAM *stream, void *value);

#endif