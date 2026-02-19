/*Process A wants to send a number to Process B. Once received, Process B has to check
whether the number is palindrome or not. Write a C program to implement this interprocess
communication using message queue.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer {
    long msg_type;
    int number;
};

int isPalindrome(int num) {
    int rev = 0, temp = num;
    while (temp > 0) {
        rev = rev * 10 + temp % 10;
        temp /= 10;
    }
    return rev == num;
}

int main() {
    key_t key = ftok("progfile", 65);
    int msgid = msgget(key, 0666 | IPC_CREAT);
    struct msg_buffer message;

    
    message.msg_type = 1;
    message.number = 121; 
    msgsnd(msgid, &message, sizeof(message), 0);

    
    msgrcv(msgid, &message, sizeof(message), 1, 0);
    printf("Received: %d\n", message.number);
    if (isPalindrome(message.number))
        printf("Palindrome\n");
    else
        printf("Not Palindrome\n");

    msgctl(msgid, IPC_RMID, NULL);
    return 0;
}
