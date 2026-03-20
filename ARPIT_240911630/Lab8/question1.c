#include <stdio.h>
#include <stdbool.h>

#define N 5
#define M 3

bool lessOrEqual(int a[], int b[]) {
    for (int i = 0; i < M; i++) {
        if (a[i] > b[i]) return false;
    }
    return true;
}

void printMatrix(const char *name, int mat[N][M]) {
    printf("\n%s:\n", name);
    printf("      A B C\n");
    for (int i = 0; i < N; i++) {
        printf("P%d -> ", i);
        for (int j = 0; j < M; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

void printVector(const char *name, int v[M]) {
    printf("\n%s: ", name);
    for (int i = 0; i < M; i++) printf("%d ", v[i]);
    printf("\n");
}

void calculateNeed(int maxm[N][M], int alloc[N][M], int need[N][M]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            need[i][j] = maxm[i][j] - alloc[i][j];
}

bool safetyCheck(int alloc[N][M], int need[N][M], int available[M], int safeSeq[N]) {
    int work[M];
    bool finish[N] = {false};
    int count = 0;

    for (int i = 0; i < M; i++) work[i] = available[i];

    while (count < N) {
        bool found = false;
        for (int i = 0; i < N; i++) {
            if (!finish[i] && lessOrEqual(need[i], work)) {
                for (int j = 0; j < M; j++) work[j] += alloc[i][j];
                safeSeq[count++] = i;
                finish[i] = true;
                found = true;
            }
        }
        if (!found) break;
    }

    return (count == N);
}

bool requestResources(int p, int req[M],
                      int alloc[N][M], int need[N][M], int available[M],
                      int safeSeq[N]) {
    // req <= need?
    if (!lessOrEqual(req, need[p])) {
        printf("Invalid request: Request > Need\n");
        return false;
    }

    // req <= available?
    if (!lessOrEqual(req, available)) {
        printf("Resources not available now.\n");
        return false;
    }

    // Tentative allocation
    for (int j = 0; j < M; j++) {
        available[j] -= req[j];
        alloc[p][j] += req[j];
        need[p][j] -= req[j];
    }

    if (safetyCheck(alloc, need, available, safeSeq)) {
        return true;
    } else {
        // Rollback
        for (int j = 0; j < M; j++) {
            available[j] += req[j];
            alloc[p][j] -= req[j];
            need[p][j] += req[j];
        }
        return false;
    }
}

void copyState(int srcA[N][M], int dstA[N][M],
               int srcN[N][M], int dstN[N][M],
               int srcV[M], int dstV[M]) {
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++) {
            dstA[i][j] = srcA[i][j];
            dstN[i][j] = srcN[i][j];
        }

    for (int j = 0; j < M; j++) dstV[j] = srcV[j];
}

int main() {
    int alloc[N][M], maxm[N][M], need[N][M], available[M];
    int safeSeq[N];

    printf("Enter Allocation matrix (5x3):\n");
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            scanf("%d", &alloc[i][j]);

    printf("Enter Max matrix (5x3):\n");
    for (int i = 0; i < N; i++)
        for (int j = 0; j < M; j++)
            scanf("%d", &maxm[i][j]);

    printf("Enter Available vector (3 values): ");
    for (int j = 0; j < M; j++) scanf("%d", &available[j]);

    calculateNeed(maxm, alloc, need);

    printMatrix("Allocation", alloc);
    printMatrix("Max", maxm);
    printMatrix("Need", need);
    printVector("Available", available);

    if (safetyCheck(alloc, need, available, safeSeq)) {
        printf("\nSystem is in SAFE state.\nSafe sequence: ");
        for (int i = 0; i < N; i++) {
            printf("P%d", safeSeq[i]);
            if (i != N - 1) printf(" -> ");
        }
        printf("\n");
    } else {
        printf("\nSystem is NOT in safe state.\n");
    }

    
    int testProc[3] = {1, 4, 0};
    int testReq[3][M] = {
        {1, 0, 2},
        {3, 3, 0}, 
        {0, 2, 0}  
    };

    for (int t = 0; t < 3; t++) {
        int p = testProc[t], req[M];
        int a2[N][M], n2[N][M], v2[M], seq2[N];

        for (int j = 0; j < M; j++) req[j] = testReq[t][j];

        copyState(alloc, a2, need, n2, available, v2);

        printf("\nTesting request from P%d: (%d,%d,%d)\n", p, req[0], req[1], req[2]);

        if (requestResources(p, req, a2, n2, v2, seq2)) {
            printf("Request GRANTED.\n");
            printMatrix("Updated Allocation", a2);
            printMatrix("Updated Need", n2);
            printVector("Updated Available", v2);

            printf("Safe sequence: ");
            for (int i = 0; i < N; i++) {
                printf("P%d", seq2[i]);
                if (i != N - 1) printf(" -> ");
            }
            printf("\n");
        } else {
            printf("Request CANNOT be granted immediately.\n");
        }
    }

    return 0;
}