/*Write a menu driven C/C++ program to simulate the following CPU scheduling algorithms.
Display Gantt chart showing the order of execution of each process. Compute waiting time and
turnaround time for each process. Hence, compute average waiting time and average turnaround
time.
(i) FCFS (ii) SRTF (iii) Round-Robin (quantum = 10 ) iv) non-preemptive priority (higher
the number higher the priority)*/
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char pid[3];
    int arrival, burst, priority;
    int waiting, turnaround, remaining;
} Process;

void fcfs(Process p[], int n);
void srtf(Process p[], int n);
void roundRobin(Process p[], int n, int quantum);
void priorityNP(Process p[], int n);

int main() {
    Process p[4] = {
        {"P1",0,60,3,0,0,60},
        {"P2",3,30,2,0,0,30},
        {"P3",4,40,1,0,0,40},
        {"P4",9,10,4,0,0,10}
    };
    int choice;
    do {
        printf("\nCPU Scheduling Menu:\n");
        printf("1. FCFS\n2. SRTF\n3. Round Robin (q=10)\n4. Non-preemptive Priority\n5. Exit\n");
        printf("Enter choice: ");
        scanf("%d",&choice);
        switch(choice) {
            case 1: fcfs(p,4); break;
            case 2: srtf(p,4); break;
            case 3: roundRobin(p,4,10); break;
            case 4: priorityNP(p,4); break;
        }
    } while(choice!=5);
    return 0;
}


void fcfs(Process p[], int n) {
    int time=0;
    printf("\nFCFS Gantt Chart:\n");
    for(int i=0;i<n;i++) {
        if(time < p[i].arrival) time = p[i].arrival;
        printf("|%s(%d-%d)", p[i].pid, time, time+p[i].burst);
        p[i].waiting = time - p[i].arrival;
        time += p[i].burst;
        p[i].turnaround = p[i].waiting + p[i].burst;
    }
    printf("|\n");
    double avgW=0, avgT=0;
    for(int i=0;i<n;i++){ avgW+=p[i].waiting; avgT+=p[i].turnaround; }
    printf("Avg Waiting=%.2f, Avg Turnaround=%.2f\n", avgW/n, avgT/n);
}

void srtf(Process p[], int n) {
    int complete=0, time=0, min, shortest;
    for(int i=0;i<n;i++) p[i].remaining=p[i].burst;
    printf("\nSRTF Gantt Chart:\n");
    while(complete<n) {
        shortest=-1; min=9999;
        for(int i=0;i<n;i++) {
            if(p[i].arrival<=time && p[i].remaining>0 && p[i].remaining<min) {
                min=p[i].remaining; shortest=i;
            }
        }
        if(shortest==-1) { time++; continue; }
        p[shortest].remaining--;
        if(p[shortest].remaining==0) {
            complete++;
            int finish=time+1;
            p[shortest].turnaround=finish-p[shortest].arrival;
            p[shortest].waiting=p[shortest].turnaround-p[shortest].burst;
        }
        time++;
    }
    double avgW=0, avgT=0;
    for(int i=0;i<n;i++){ avgW+=p[i].waiting; avgT+=p[i].turnaround; }
    printf("Avg Waiting=%.2f, Avg Turnaround=%.2f\n", avgW/n, avgT/n);
}


void roundRobin(Process p[], int n, int quantum) {
    int time=0, remain=n;
    for(int i=0;i<n;i++) p[i].remaining=p[i].burst;
    printf("\nRound Robin Gantt Chart:\n");
    while(remain>0) {
        for(int i=0;i<n;i++) {
            if(p[i].remaining>0 && p[i].arrival<=time) {
                int exec = (p[i].remaining>quantum)?quantum:p[i].remaining;
                printf("|%s(%d-%d)", p[i].pid, time, time+exec);
                time+=exec;
                p[i].remaining-=exec;
                if(p[i].remaining==0) {
                    remain--;
                    p[i].turnaround=time-p[i].arrival;
                    p[i].waiting=p[i].turnaround-p[i].burst;
                }
            }
        }
    }
    printf("|\n");
    double avgW=0, avgT=0;
    for(int i=0;i<n;i++){ avgW+=p[i].waiting; avgT+=p[i].turnaround; }
    printf("Avg Waiting=%.2f, Avg Turnaround=%.2f\n", avgW/n, avgT/n);
}


void priorityNP(Process p[], int n) {
    int done[n]; for(int i=0;i<n;i++) done[i]=0;
    int time=0, completed=0;
    printf("\nPriority Gantt Chart:\n");
    while(completed<n) {
        int idx=-1, max=-1;
        for(int i=0;i<n;i++) {
            if(!done[i] && p[i].arrival<=time && p[i].priority>max) {
                max=p[i].priority; idx=i;
            }
        }
        if(idx==-1){ time++; continue; }
        printf("|%s(%d-%d)", p[idx].pid, time, time+p[idx].burst);
        p[idx].waiting=time-p[idx].arrival;
        time+=p[idx].burst;
        p[idx].turnaround=p[idx].waiting+p[idx].burst;
        done[idx]=1; completed++;
    }
    printf("|\n");
    double avgW=0, avgT=0;
    for(int i=0;i<n;i++){ avgW+=p[i].waiting; avgT+=p[i].turnaround; }
    printf("Avg Waiting=%.2f, Avg Turnaround=%.2f\n", avgW/n, avgT/n);
}
