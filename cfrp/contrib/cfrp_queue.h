#ifndef CFRP_QUEUE_H
#define CFRP_QUEUE_H

#include "cfrp_list.h"

typedef struct CFRP_QUEUE CFRP_QUEUE;
struct CFRP_QUEUE {
  CFRP_LIST *list;
};

CFRP_QUEUE *cfrp_create_queue();

void cfrp_enqueue(CFRP_QUEUE *queue, void *element);

void *cfrp_dequeue(CFRP_QUEUE *queue);

int cfrp_queue_is_empty(CFRP_QUEUE *queue);

#endif