#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

struct data {
  int x;
  pthread_mutex_t mutex;
};

void *increment(void *void_ptr) {
  int i = 0;
  struct data *args = (struct data *)void_ptr;

  while(++i <= 100000) {
    pthread_mutex_lock(&args->mutex);
    args->x = args->x + 1;
    pthread_mutex_unlock(&args->mutex);
  }
  return void_ptr;
}

int main() {
  pthread_t thread0, thread1;
  struct data args;
  args.x = 0;

  pthread_mutex_init(&args.mutex, NULL);

  pthread_create(&thread0, NULL, increment, &args);
  pthread_create(&thread1, NULL, increment, &args);
  pthread_join(thread0, NULL);
  pthread_join(thread1, NULL);

  printf("x is now %d\n", args.x);

  return 0;
}
