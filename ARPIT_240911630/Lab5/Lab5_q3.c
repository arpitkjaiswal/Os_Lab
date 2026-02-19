/*3. Write a C program to simulate Earliest-Deadline-First scheduling for real time systems.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

typedef struct {
    char id[16];
    int at;
    int c;
    int rem;
    int dl;
    int st, ct;
    int missed;
} Task;

int main(){
    int n;
    printf("EDF Scheduler (preemptive)\nEnter number of tasks: "); scanf("%d",&n);
    Task t[50];
    for (int i=0;i<n;i++){
        printf("Task ID: "); scanf("%s", t[i].id);
        printf("Arrival time: "); scanf("%d", &t[i].at);
        printf("Computation time: "); scanf("%d", &t[i].c);
        printf("Absolute deadline: "); scanf("%d", &t[i].dl);
        t[i].rem = t[i].c; t[i].st=-1; t[i].ct=-1; t[i].missed=0;
    }
    int time=0, completed=0;
    for (int i=0;i<n;i++) for (int j=i+1;j<n;j++) if (t[j].at < t[i].at) { Task tmp=t[i]; t[i]=t[j]; t[j]=tmp; }
    printf("\nGantt:\n|");
    while (completed < n) {
        int idx=-1; int earliest=INT_MAX;
        for (int i=0;i<n;i++){
            if (t[i].at <= time && t[i].rem>0) {
                if (t[i].dl < earliest) { earliest = t[i].dl; idx = i; }
                else if (t[i].dl == earliest) {
                    if (t[i].at < t[idx].at) idx = i;
                }
            }
        }
        if (idx==-1) {
            int nextAt = INT_MAX;
            for (int i=0;i<n;i++) if (t[i].rem>0) nextAt = (t[i].at < nextAt) ? t[i].at : nextAt;
            if (nextAt==INT_MAX) break;
            printf(" idle |");
            time = nextAt;
            continue;
        }
        if (t[idx].st==-1) t[idx].st = time;
        printf(" %s |", t[idx].id);
        t[idx].rem -= 1;
        time += 1;
        if (t[idx].rem==0) {
            t[idx].ct = time;
            completed++;
            if (t[idx].ct > t[idx].dl) t[idx].missed = 1;
        }
        for (int i=0;i<n;i++) {
            if (t[i].rem>0 && t[i].dl < time) t[i].missed = 1;
        }
    }
    printf("\n\nResults:\nID AT C DL ST CT TAT WT Missed\n");
    double avgT=0, avgW=0;
    for (int i=0;i<n;i++){
        int tat = t[i].ct - t[i].at;
        int wt = tat - t[i].c;
        printf("%s %d %d %d %d %d %d %d %s\n", t[i].id, t[i].at, t[i].c, t[i].dl, t[i].st, t[i].ct, tat, wt, t[i].missed ? "YES":"NO");
        avgT += tat; avgW += wt;
    }
    printf("Average TAT=%.2f, Average WT=%.2f\n", avgT/n, avgW/n);
    return 0;
}
