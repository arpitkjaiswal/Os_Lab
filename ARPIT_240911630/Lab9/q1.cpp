#include <stdio.h>
#include <string.h>

void simulate(char* type, int b_orig[], int n, int p[], int m) {
    int blocks[10], allocation[10];
    for (int i = 0; i < n; i++) blocks[i] = b_orig[i];
    for (int i = 0; i < m; i++) allocation[i] = -1;

    for (int i = 0; i < m; i++) {
        int index = -1;
        for (int j = 0; j < n; j++) {
            if (blocks[j] >= p[i]) {
                if (strcmp(type, "First") == 0) {
                    index = j;
                    break;
                } else if (strcmp(type, "Best") == 0) {
                    if (index == -1 || blocks[j] < blocks[index]) index = j;
                } else if (strcmp(type, "Worst") == 0) {
                    if (index == -1 || blocks[j] > blocks[index]) index = j;
                }
            }
        }
        if (index != -1) {
            allocation[i] = index;
            blocks[index] -= p[i];
        }
    }

    printf("\n%s Fit Allocation:\nProc\tSize\tBlock\n", type);
    for (int i = 0; i < m; i++) {
        printf("%d\t%dK\t", i + 1, p[i]);
        if (allocation[i] != -1) printf("%d\n", allocation[i] + 1);
        else printf("Not Allocated\n");
    }
}

int main() {
    int b[] = {100, 500, 200, 300, 600};
    int p[] = {212, 417, 112, 426};
    int n = 5, m = 4;

    simulate("First", b, n, p, m);
    simulate("Best", b, n, p, m);
    simulate("Worst", b, n, p, m);

    return 0;
}