#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

struct data {
  int x;
  pthread_mutex_t mutex;
};

void *increment(void *void_ptr) {
  int i = 0;
  struct data *dat = (struct data *)void_ptr;

  while(++i <= 100000) {
    pthread_mutex_lock(&dat->mutex);
    dat->x = dat->x + 1;
    pthread_mutex_unlock(&dat->mutex);
  }
  return void_ptr;
}

int main() {
  pthread_t thread0, thread1;
  struct data d;

  pthread_mutex_init(&d.mutex, NULL);

  pthread_create(&thread0, NULL, increment, &d);
  pthread_create(&thread1, NULL, increment, &d);
  pthread_join(thread0, NULL);
  pthread_join(thread1, NULL);

  printf("x is now %d\n", d.x);

  return 0;
}
