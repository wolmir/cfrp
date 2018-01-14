#include <stdlib.h>

#include "cfrp_queue.h"
#include "cfrp_list.h"

CFRP_QUEUE *cfrp_create_queue(int initial_length)
{
  CFRP_QUEUE *queue;

  queue = (CFRP_QUEUE*)malloc(sizeof(CFRP_QUEUE));

  queue->list = cfrp_create_list(initial_length);

  return queue;
}

void cfrp_enqueue(CFRP_QUEUE *queue, void *element)
{
  cfrp_list_append(queue->list, element);
}

void *cfrp_dequeue(CFRP_QUEUE *queue)
{
  return cfrp_list_pop_head(queue->list);
}

int cfrp_queue_is_empty(CFRP_QUEUE *queue)
{
  return cfrp_list_is_empty(queue->list);
}
