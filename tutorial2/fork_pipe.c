#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void* doSum(void *addr) {
    int *addr_as_intptr = (int *)addr;

    for(int i = 0; i < 50000; ++i)  {
	*addr_as_intptr += 1;
    }

    return NULL;
}

int main(const int argc, const char **argv) {
    int sum;
    int pipe_fds[2];
    int *read_fd = &pipe_fds[0];
    int *write_fd = &pipe_fds[1];
    pipe(pipe_fds);

    pid_t pid = fork();
    doSum(&sum);


    if(pid == 0) {
	int other_sum;
	read(*read_fd, &other_sum, sizeof(int)); 
	printf("The sum is: %d\n", sum + other_sum);
    } else {
	write(*write_fd, &sum, sizeof(int));
    }
}
