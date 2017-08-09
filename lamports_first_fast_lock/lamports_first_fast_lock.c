#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "minunit.h"

#define NUM_THREADS 5
#define INCREMENT_AMOUNT 10000
int tests_run = 0;

struct data {
  int x;
};

void *increment(void *args_void_ptr) {
  int i = 0;
  struct data *args = (struct data *)args_void_ptr;

  while(++i <= INCREMENT_AMOUNT) {
    args->x = args->x + 1;
  }
  return args;
}

static char * test_mutex_lock() {
  pthread_t thread_list[NUM_THREADS];
  struct data args = { .x = 0 };
  int i;

  for(i = 0; i < NUM_THREADS; ++i) {
    pthread_create(&thread_list[i], NULL, increment, &args);
  }

  for(i = 0; i < NUM_THREADS; ++i) {
    pthread_join(thread_list[i], NULL);
  }

  if(args.x != 50000) { printf("x is %d\n", args.x); }
  mu_assert("error, x != 50000", args.x == 50000);

  return 0;
}

static char * all_tests() {
  mu_run_test(test_mutex_lock);

  return 0;
}

int main(int argc, char **argv) {
  mu_run_tests_and_report();

  return 0;
}
