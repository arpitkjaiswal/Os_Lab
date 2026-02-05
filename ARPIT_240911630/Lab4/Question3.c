#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <i386-linux-gnu/sys/types.h>

int main() {
    pid_t pid;

    pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } 
    else if (pid == 0) {
        printf("Child process: PID = %d\n", getpid());
        exit(0);   
    } 
    else {

        printf("Parent process: PID = %d\n", getpid());
        printf("Sleeping... child will be zombie until parent exits.\n");
        sleep(20);  
        printf("Parent exiting now.\n");
    }

    return 0;
}
