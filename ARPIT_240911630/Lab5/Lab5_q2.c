/*2. Write a C program to simulate multi-level feedback queue scheduling algorithm*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXP 50
#define AGE_INTERVAL 50

typedef struct {
    char id[16];
    int at, bt, rem;
    int st, ct;
} Proc;

typedef struct Node {
    int idx;
    struct Node* next;
} Node;

void push(Node** head, int idx) {
    Node* n = (Node*)malloc(sizeof(Node)); n->idx=idx; n->next=NULL;
    if (!*head) { *head = n; return; }
    Node* t = *head; while (t->next) t=t->next; t->next=n;
}
int pop(Node** head) {
    if (!*head) return -1;
    Node* t = *head; int idx = t->idx; *head = t->next; free(t); return idx;
}
int empty(Node* head) { return head==NULL; }

int main(){
    int n;
    printf("MLFQ Simulator\nEnter number of processes: "); scanf("%d",&n);
    Proc p[MAXP];
    for (int i=0;i<n;i++){
        printf("ID: "); scanf("%s", p[i].id);
        printf("Arrival time: "); scanf("%d",&p[i].at);
        printf("Burst time: "); scanf("%d",&p[i].bt);
        p[i].rem = p[i].bt; p[i].st=-1; p[i].ct=-1;
    }
    Node *q0=NULL, *q1=NULL, *q2=NULL;
    int time=0, completed=0;
    int lastPromotionCheck = 0;
    int waitSince[MAXP]; for (int i=0;i<n;i++) waitSince[i]=p[i].at;
    for (int i=0;i<n;i++) for (int j=i+1;j<n;j++) if (p[j].at < p[i].at) { Proc t=p[i]; p[i]=p[j]; p[j]=t; }
    int nextArr = 0;
    printf("\nGantt:\n|");
    while (completed < n) {
        while (nextArr < n && p[nextArr].at <= time) { push(&q0, nextArr); nextArr++; }
        if (time - lastPromotionCheck >= AGE_INTERVAL) {
            lastPromotionCheck = time;
            for (int i=0;i<n;i++) {
                if (p[i].rem>0 && p[i].at < time) {
                    int waited = time - waitSince[i];
                    if (waited >= AGE_INTERVAL*2) {
                        push(&q0, i);
                        waitSince[i] = time;
                    }
                }
            }
        }
        int idx = -1, quantum=0;
        if (!empty(q0)) { idx = pop(&q0); quantum = 8; }
        else if (!empty(q1)) { idx = pop(&q1); quantum = 16; }
        else if (!empty(q2)) { idx = pop(&q2); quantum = 1000000; }
        else {
            if (nextArr < n) { int idle = p[nextArr].at - time; printf(" idle |"); time = p[nextArr].at; continue; }
            else break;
        }
        if (p[idx].st==-1) p[idx].st = time;
        int exec = (p[idx].rem < quantum) ? p[idx].rem : quantum;
        printf(" %s |", p[idx].id);
        p[idx].rem -= exec;
        time += exec;
        if (p[idx].rem==0) { p[idx].ct = time; completed++; }
        else {
            if (quantum==8) push(&q1, idx);
            else if (quantum==16) push(&q2, idx);
            else push(&q2, idx);
        }
    }
    printf("\n\nResults:\nID AT BT ST CT TAT WT\n");
    double avgT=0, avgW=0;
    for (int i=0;i<n;i++){
        int tat = p[i].ct - p[i].at;
        int wt = tat - p[i].bt;
        printf("%s %d %d %d %d %d %d\n", p[i].id, p[i].at, p[i].bt, p[i].st, p[i].ct, tat, wt);
        avgT += tat; avgW += wt;
    }
    printf("Average TAT=%.2f, Average WT=%.2f\n", avgT/n, avgW/n);
    return 0;
}
