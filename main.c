#include <stdio.h>
#include <stdlib.h>

#include "c_frp.h"
#include "cfrp_int.h"

void *print_values(void *value);
void *mult_value(void *value);
void *mult_value_by_four(void *value);

int main()
{
  EVENT_STREAM *test_stream;
  EVENT_STREAM *mult_stream;
  EVENT_STREAM *other_mult_stream;
  CFRP_INT *numa = cfrp_int_of(3);
  CFRP_INT *numb = cfrp_int_of(5);
  CFRP_INT *numc = cfrp_int_of(8);
  CFRP_INT *numd = cfrp_int_of(13);

  test_stream = cfrp_create_event_stream();

  cfrp_stream_send(test_stream, numa);
  cfrp_stream_send(test_stream, numb);

  mult_stream = cfrp_stream_map(test_stream, mult_value);
  other_mult_stream = cfrp_stream_map(test_stream, mult_value_by_four);

  cfrp_stream_tap(mult_stream, print_values);
  cfrp_stream_tap(other_mult_stream, print_values);

  cfrp_stream_send(test_stream, numc);
  cfrp_stream_send(test_stream, numd);

  return 0;
}

void *mult_value(void *value)
{
  return cfrp_int_mult((CFRP_INT*)value, 3);
}

void *mult_value_by_four(void *value)
{
  return cfrp_int_mult((CFRP_INT*)value, 4);
}

void *print_values(void *value)
{
  int actual_value = cfrp_int_get_value((CFRP_INT*)value);

  printf("Value: %d\n", actual_value);

  return NULL;
}