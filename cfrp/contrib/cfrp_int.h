#ifndef CFRP_INT_H
#define CFRP_INT_H

typedef struct CFRP_INT CFRP_INT;
struct CFRP_INT {
  int value;
};

CFRP_INT *cfrp_int_of(int n);
CFRP_INT *cfrp_int_add(CFRP_INT *p, int n);
CFRP_INT *cfrp_int_mult(CFRP_INT *p, int n);

int cfrp_int_get_value(CFRP_INT* container);

#endif