#include <stdio.h>

#include "c_frp.h"

void *print_values(void *value);

int main()
{
  EVENT_STREAM *test_stream;
  EVENT_STREAM *listener;
  int numa = 3;
  int numb = 5;
  int numc = 8;

  test_stream = cfrp_create_event_stream();

  cfrp_stream_send(test_stream, &numa);
  cfrp_stream_send(test_stream, &numb);

  listener = cfrp_stream_tap(test_stream, print_values);

  cfrp_stream_send(test_stream, &numc);

  return 0;
}

void *print_values(void *value)
{
  printf("Value: %d\n", *((int*)value));

  return NULL;
}