/*Implement a parent process, which sends an English alphabet to child process using shared
memory. Child process responds back with next English alphabet to the parent. Parent
displays the reply from the Child.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
    key_t key = ftok("shmfile",65);
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    char *str = (char*) shmat(shmid,(void*)0,0);

    if (fork() == 0) {
   
        char c = str[0];
        str[1] = c + 1;
        shmdt(str);
    } else {
        
        str[0] = 'A';
        sleep(1);
        printf("Child replied: %c\n", str[1]);
        shmdt(str);
        shmctl(shmid,IPC_RMID,NULL);
    }
    return 0;
}
