#include <stdio.h>
#include <pthread.h>

void* doSum(void *addr) {
    int *addr_as_intptr = (int *)addr;

    for(int i = 0; i < 50000; ++i)  {
        *addr_as_intptr = *addr_as_intptr + 1;
    }

    return NULL;
}

int main(const int argc, const char **argv) {
    int sum;

    pthread_t t1, t2;

    pthread_create(&t1, NULL, &doSum, &sum);
    pthread_create(&t2, NULL, &doSum, &sum);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    printf("The sum is: %d\n", sum);
}
