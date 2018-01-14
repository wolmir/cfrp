#ifndef CFRP_LIST_H
#define CFRP_LIST_H

typedef struct LIST_NODE LIST_NODE;
struct LIST_NODE {
  void *element;
  LIST_NODE *next;
  LIST_NODE *previous;
};

typedef struct CFRP_LIST CFRP_LIST;
struct CFRP_LIST {
  int length;
  LIST_NODE *head;
  LIST_NODE *tail;
};

CFRP_LIST *cfrp_create_list();

void cfrp_list_append(CFRP_LIST *list, void *element);

void cfrp_list_foreach(CFRP_LIST *list, void (*iteratee) (void* element, void* arg), void *extra);  // 'extra' becomes 'arg'

void *cfrp_list_pop_head(CFRP_LIST *list);

int cfrp_list_is_empty(CFRP_LIST *list);

#endif