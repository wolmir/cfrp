#ifndef CFRP_INTERNAL_H
#define CFRP_INTERNAL_H

#include "cfrp.h"

void cfrp_notify(void *_stream, void *notification);
void cfrp_notify_tap(void *_stream, void *arg); // The last argument is merely for the foreach compatibility

#endif