#include <stdlib.h>
#include <assert.h>

#include "cfrp_int.h"

CFRP_INT *cfrp_int_of(int n)
{
  CFRP_INT *container = (CFRP_INT*)malloc(sizeof(CFRP_INT));

  container->value = n;

  return container;
}

CFRP_INT *cfrp_int_add(CFRP_INT *p, int n)
{
  assert(p != NULL);

  return cfrp_int_of(p->value + n);
}

CFRP_INT *cfrp_int_mult(CFRP_INT *p, int n)
{
  assert(p != NULL);

  return cfrp_int_of(p->value * n);
}

int cfrp_int_get_value(CFRP_INT* container)
{
  assert(container != NULL);

  return container->value;
}
