#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/mman.h>

void* doSum(void *addr) {
    int *addr_as_intptr = (int *)addr;

    for(int i = 0; i < 50000; ++i)  {
	*addr_as_intptr += 1;
    }

    return NULL;
}

int main(const int argc, const char **argv) {
    int *sum = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);

    // Note that since we aren't using a lock we will run into similar problems as fork.c
    pid_t pid = fork();
    doSum(sum);

    if(pid == 0) {
	wait(NULL);
	printf("The sum is: %d\n", *sum);
    }
}
