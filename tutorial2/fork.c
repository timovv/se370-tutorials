#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void* doSum(void *addr) {
    int *addr_as_intptr = (int *)addr;

    for(int i = 0; i < 50000; ++i)  {
	*addr_as_intptr += 1;
    }

    return NULL;
}

int main(const int argc, const char **argv) {
    int sum;

    pid_t pid = fork();
    doSum(&sum);

    if(pid != 0) {
	wait(NULL);
	printf("The sum is: %d\n", sum);
    }
}
