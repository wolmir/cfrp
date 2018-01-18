#include <stdio.h>
#include <stdlib.h>

#include "cfrp/cfrp.h"
#include "cfrp/contrib/cfrp_int.h"

void *print_values(void *value);
void *greater_than_six(void *value);

int main()
{
  EVENT_STREAM *test_stream;
  EVENT_STREAM *second_stream;
  EVENT_STREAM *merged_stream;
  CFRP_INT *numa = cfrp_int_of(3);
  CFRP_INT *numb = cfrp_int_of(5);
  CFRP_INT *numc = cfrp_int_of(8);
  CFRP_INT *numd = cfrp_int_of(13);

  test_stream = cfrp_create_event_stream();
  second_stream = cfrp_create_event_stream();

  EVENT_STREAM* test_and_second[2] = {test_stream, second_stream};

  merged_stream = cfrp_stream_merge(test_and_second, 2);

  cfrp_stream_send(test_stream, numa);
  cfrp_stream_send(second_stream, numb);
  cfrp_stream_send(test_stream, numc);
  cfrp_stream_send(second_stream, numd);

  cfrp_stream_tap(merged_stream, print_values);

  return 0;
}

void *greater_than_six(void *value)
{
  return cfrp_bool(cfrp_int_get_value((CFRP_INT*)value) > 6);
}

void *print_values(void *value)
{
  int actual_value = cfrp_int_get_value((CFRP_INT*)value);

  printf("Value: %d\n", actual_value);

  return NULL;
}