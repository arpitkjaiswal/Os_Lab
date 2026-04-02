#include <stdio.h>

int main() {
    const int PAGE_SIZE = 32;
    const int TOTAL_PAGES = 8;
    const int TOTAL_MEMORY = PAGE_SIZE * TOTAL_PAGES; 
    int addresses[] = {204, 56};
    int n = sizeof(addresses) / sizeof(addresses[0]);

    printf("Total memory: %d bytes\n", TOTAL_MEMORY);
    printf("Address size needed: 8 bits = 1 byte\n\n");

    for (int i = 0; i < n; i++) {
        int logical = addresses[i];

        if (logical < 0 || logical >= TOTAL_MEMORY) {
            printf("Logical address %d is invalid (0-%d allowed)\n", logical, TOTAL_MEMORY - 1);
            continue;
        }

        int page_number = logical / PAGE_SIZE;
        int page_offset = logical % PAGE_SIZE;

        printf("Logical address: %d\n", logical);
        printf("Page number    : %d\n", page_number);
        printf("Page offset    : %d\n\n", page_offset);
    }

    return 0;
}