#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        exit(1);
    } 
    else if (pid == 0) {
        
        printf("Child: About to execute external program...\n");

        
        if (execl("./childprog", "childprog", (char *)NULL) == -1) {
            perror("execl failed");
            exit(1);
        }
    } 
    else {
       
        wait(NULL);
        printf("Parent: Child has finished executing external program.\n");
    }

    return 0;
}
