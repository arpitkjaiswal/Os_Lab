/*Write a producer and consumer program in C using FIFO queue. The producer should write
a set of 4 integers into the FIFO queue and the consumer should display the 4 integers.*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main() {
    int fd;
    int arr[4] = {10, 20, 30, 40};
    int recv[4];

    
    mkfifo("myfifo", 0666);

    if (fork() == 0) {
   
        fd = open("myfifo", O_RDONLY);
        read(fd, recv, sizeof(recv));
        printf("Consumer received: ");
        for (int i = 0; i < 4; i++) printf("%d ", recv[i]);
        printf("\n");
        close(fd);
        unlink("myfifo"); 
    } else {
       
        fd = open("myfifo", O_WRONLY);
        write(fd, arr, sizeof(arr));
        close(fd);
        wait(NULL); 
    }

    return 0;
}


