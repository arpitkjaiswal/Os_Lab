#include <stdio.h>
#include <stdlib.h>

int fifoPageReplacement(int pages[], int n, int frames) {
    int *memory = (int*)malloc(frames * sizeof(int));
    int count = 0, index = 0, pageFaults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int hit = 0;

        for (int j = 0; j < count; j++) {
            if (memory[j] == page) {
                hit = 1;
                break;
            }
        }

        if (!hit) {
            pageFaults++;
            if (count < frames) {
                memory[count++] = page;
            } else {
                memory[index] = page;
                index = (index + 1) % frames;
            }
        }
    }
    free(memory);
    return pageFaults;
}

int optimalPageReplacement(int pages[], int n, int frames) {
    int *memory = (int*)malloc(frames * sizeof(int));
    int count = 0, pageFaults = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int hit = 0;

        for (int j = 0; j < count; j++) {
            if (memory[j] == page) {
                hit = 1;
                break;
            }
        }

        if (!hit) {
            pageFaults++;
            if (count < frames) {
                memory[count++] = page;
            } else {
                int replaceIndex = -1, farthest = i + 1;
                for (int j = 0; j < frames; j++) {
                    int nextUse = -1;
                    for (int k = i + 1; k < n; k++) {
                        if (memory[j] == pages[k]) {
                            nextUse = k;
                            break;
                        }
                    }
                    if (nextUse == -1) {
                        replaceIndex = j;
                        break;
                    }
                    if (nextUse > farthest) {
                        farthest = nextUse;
                        replaceIndex = j;
                    }
                }
                memory[replaceIndex] = page;
            }
        }
    }
    free(memory);
    return pageFaults;
}

int main() {
    int n, frames;
    printf("Enter number of pages: ");
    scanf("%d", &n);

    int *pages = (int*)malloc(n * sizeof(int));
    printf("Enter page reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);

    printf("Enter number of frames: ");
    scanf("%d", &frames);

    printf("FIFO Page Faults: %d\n", fifoPageReplacement(pages, n, frames));
    printf("Optimal Page Faults: %d\n", optimalPageReplacement(pages, n, frames));

    free(pages);
    return 0;
}
