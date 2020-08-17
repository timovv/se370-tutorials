#include <pthread.h>
#include <unistd.h>
#include <stdio.h>

#define NUM_THREADS 5

static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
static int count = 0;

void *cond_thread(void *id) {
    int thread_id = (int)(long)id; // Never do this in your code.

    for(int i = 0; i < 5; ++i) {
	sleep(1);
	printf("thread %d: working hard [%d/5]\n", thread_id, i + 1);
    }

    // we've done our 'work', so update the count and signal that we've changed it
    pthread_mutex_lock(&mutex);
    ++count;
    printf("thread %d: done!\n", thread_id);
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex);

    return NULL;
}

int main(int argc, const char **argv) {
    pthread_t threads[NUM_THREADS];
    for(int i = 0; i < NUM_THREADS; ++i) {
	pthread_create(&threads[i], NULL, cond_thread, (void *)(long)(i + 1));
    }

    printf("main thread: start\n");
    pthread_mutex_lock(&mutex);
    while(count != NUM_THREADS) {
	pthread_cond_wait(&cond, &mutex);
	printf("main thread: awoke, count is now %d\n", count);
    }

    printf("main thread: done\n");
}
