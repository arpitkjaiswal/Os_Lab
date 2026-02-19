/*Write a producer-consumer program in C in which producer writes a set of words into shared
memory and then consumer reads the set of words from the shared memory. The shared
memory need to be detached and deleted after use.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>

int main() {
    key_t key = ftok("shmfile",65);
    int shmid = shmget(key,1024,0666|IPC_CREAT);
    char *str = (char*) shmat(shmid,(void*)0,0);

    if (fork() == 0) {
      
        sleep(1);
        printf("Consumer read: %s\n", str);
        shmdt(str);
        shmctl(shmid,IPC_RMID,NULL);
    } else {
       
        strcpy(str, "Hello IPC Shared Memory");
        shmdt(str);
    }
    return 0;
}
