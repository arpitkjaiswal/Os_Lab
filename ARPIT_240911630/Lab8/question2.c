#include <stdio.h>
#include <stdbool.h>

#define N 5
#define M 3

bool canProceed(int req[M], int work[M]) {
    for (int i = 0; i < M; i++) {
        if (req[i] > work[i]) return false;
    }
    return true;
}

void printMatrix(const char *name, int mat[N][M]) {
    printf("\n%s:\n", name);
    printf("      A B C\n");
    for (int i = 0; i < N; i++) {
        printf("P%d -> ", i);
        for (int j = 0; j < M; j++) printf("%d ", mat[i][j]);
        printf("\n");
    }
}

bool detectDeadlock(int alloc[N][M], int req[N][M], int available[M],
                    int order[N], int *orderCount, int deadlocked[N], int *deadCount) {
    int work[M];
    bool finish[N] = {false};

    *orderCount = 0;
    *deadCount = 0;

    for (int i = 0; i < M; i++) work[i] = available[i];

    while (1) {
        bool progressed = false;
        for (int i = 0; i < N; i++) {
            if (!finish[i] && canProceed(req[i], work)) {
                for (int j = 0; j < M; j++) work[j] += alloc[i][j];
                finish[i] = true;
                order[(*orderCount)++] = i;
                progressed = true;
            }
        }
        if (!progressed) break;
    }

    for (int i = 0; i < N; i++) {
        if (!finish[i]) deadlocked[(*deadCount)++] = i;
    }

    return (*deadCount == 0);
}

int main() {
    int alloc[N][M], req[N][M], available[M];
    int order[N], deadlocked[N], orderCount, deadCount;

    printf("Enter Allocation matrix (5x3):\n");
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Request matrix (5x3):\n");
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            scanf("%d", &req[i][j]);

    printf("Enter Available vector (3 values): ");
    for (int j = 0; j < M; j++) scanf("%d", &available[j]);

    printMatrix("Allocation", alloc);
    printMatrix("Request", req);

    if (detectDeadlock(alloc, req, available, order, &orderCount, deadlocked, &deadCount)) {
        printf("\nNo deadlock detected.\nCompletion order: ");
        for (int i = 0; i < orderCount; i++) {
            printf("P%d", order[i]);
            if (i != orderCount - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("\nDeadlock detected.\nDeadlocked processes: ");
        for (int i = 0; i < deadCount; i++) printf("P%d ", deadlocked[i]);
        printf("\n");
    }

    
    int req2[N][M];
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            req2[i][j] = req[i][j];

    req2[2][2] += 1; 
    printf("\nTesting part (b): P2 requests one additional C.\n");

    if (detectDeadlock(alloc, req2, available, order, &orderCount, deadlocked, &deadCount)) {
        printf("Still NO deadlock.\nCompletion order: ");
        for (int i = 0; i < orderCount; i++) {
            printf("P%d", order[i]);
            if (i != orderCount - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("Deadlock occurs after extra request.\nDeadlocked processes: ");
        for (int i = 0; i < deadCount; i++) printf("P%d ", deadlocked[i]);
        printf("\n");
    }

    return 0;
}