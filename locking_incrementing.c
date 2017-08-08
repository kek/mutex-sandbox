#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_THREADS 5

struct data {
  int x;
  pthread_mutex_t mutex;
};

void *increment(void *args_void_ptr) {
  int i = 0;
  struct data *args = (struct data *)args_void_ptr;

  while(++i <= 10000) {
    pthread_mutex_lock(&args->mutex);
    args->x = args->x + 1;
    pthread_mutex_unlock(&args->mutex);
  }
  return args;
}

int main() {
  pthread_t thread_list[NUM_THREADS];
  struct data args = { .x = 0 };
  int i;

  pthread_mutex_init(&args.mutex, NULL);

  for(i = 0; i < NUM_THREADS; ++i) {
    pthread_create(&thread_list[i], NULL, increment, &args);
  }

  for(i = 0; i < NUM_THREADS; ++i) {
    pthread_join(thread_list[i], NULL);
  }

  printf("x is now %d\n", args.x);

  return 0;
}
