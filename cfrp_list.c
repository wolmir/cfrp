#include <stdlib.h>

#include "cfrp_list.h"

CFRP_LIST *cfrp_create_list()
{
  CFRP_LIST *list;

  list = (CFRP_LIST*)malloc(sizeof(CFRP_LIST));
  list->length = 0;
  list->head = NULL;
  list->tail = NULL;

  return list;
}

void cfrp_list_foreach(CFRP_LIST *list, void (*iteratee) (void* element, void* arg), void *extra)
{
  LIST_NODE *current_node;

  current_node = list->head;

  while (current_node != NULL) {
    iteratee(current_node->element, extra);

    current_node = current_node->next;
  }
}

void cfrp_list_append(CFRP_LIST *list, void *element)
{
  if (list->head == NULL) {
    list->head = (LIST_NODE*)malloc(sizeof(LIST_NODE));

    list->head->next = NULL;
    list->head->previous = NULL;
    list->head->element = element;

    list->tail = list->head;
  } else {
    list->tail->next = (LIST_NODE*)malloc(sizeof(LIST_NODE));

    list->tail->next->previous = list->tail;

    list->tail = list->tail->next;

    list->tail->element = element;
  }
}

void *cfrp_list_pop_head(CFRP_LIST *list)
{
  if (list->head == NULL) {
    return NULL;
  }

  void *element = list->head->element;

  LIST_NODE *tmp = list->head;

  list->head = list->head->next;

  if (list->head != NULL) {
    list->head->previous = NULL;
  }

  free(tmp);

  return element;
}

int cfrp_list_is_empty(CFRP_LIST *list)
{
  return list->head == NULL;
}
