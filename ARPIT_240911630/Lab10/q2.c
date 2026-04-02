#include <stdio.h>
#include <stdlib.h>

int lruPageReplacement(int pages[], int n, int frames) {
    int *memory = (int*)malloc(frames * sizeof(int));
    int *lastUsed = (int*)malloc(frames * sizeof(int));
    int count = 0, pageFaults = 0, hits = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int hit = 0;

        for (int j = 0; j < count; j++) {
            if (memory[j] == page) {
                hit = 1;
                hits++;
                lastUsed[j] = i;
                break;
            }
        }

        if (!hit) {
            pageFaults++;
            if (count < frames) {
                memory[count] = page;
                lastUsed[count] = i;
                count++;
            } else {
                int lruIndex = 0;
                for (int j = 1; j < frames; j++) {
                    if (lastUsed[j] < lastUsed[lruIndex]) {
                        lruIndex = j;
                    }
                }
                memory[lruIndex] = page;
                lastUsed[lruIndex] = i;
            }
        }
    }

    printf("LRU Page Faults: %d\n", pageFaults);
    printf("Hit Ratio: %.2f\n", (double)hits / n);

    free(memory);
    free(lastUsed);
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

    lruPageReplacement(pages, n, frames);

    free(pages);
    return 0;
}
