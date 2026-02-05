#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include <string.h>


typedef struct {
    int *arr;
    int n;
    char algo_name[20];
} SortData;


void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void bubble_sort(int *arr, int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}


void insertion_sort(int *arr, int n) {
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = key;
    }
}


void selection_sort(int *arr, int n) {
    for (int i = 0; i < n-1; i++) {
        int min_idx = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
            }
        }
        swap(&arr[min_idx], &arr[i]);
    }
}


void* sort_thread(void* arg) {
    SortData *data = (SortData*) arg;

    
    int *arr_copy = malloc(data->n * sizeof(int));
    memcpy(arr_copy, data->arr, data->n * sizeof(int));

    clock_t start = clock();

    if (strcmp(data->algo_name, "Bubble") == 0) {
        bubble_sort(arr_copy, data->n);
    } else if (strcmp(data->algo_name, "Insertion") == 0) {
        insertion_sort(arr_copy, data->n);
    } else if (strcmp(data->algo_name, "Selection") == 0) {
        selection_sort(arr_copy, data->n);
    }

    clock_t end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%s Sort completed in %.6f seconds. Result: ", data->algo_name, time_taken);
    for (int i = 0; i < data->n; i++) {
        printf("%d ", arr_copy[i]);
    }
    printf("\n");

    free(arr_copy);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <number_of_elements> <elements...>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (argc != n + 2) {
        printf("Error: You must provide exactly %d elements.\n", n);
        return 1;
    }

    int *arr = malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        arr[i] = atoi(argv[i+2]);
    }

    
    const char *algos[] = {"Bubble", "Insertion", "Selection"};
    int num_algos = 3;

    pthread_t threads[num_algos];
    SortData data[num_algos];

    
    for (int i = 0; i < num_algos; i++) {
        data[i].arr = arr;
        data[i].n = n;
        strcpy(data[i].algo_name, algos[i]);
        pthread_create(&threads[i], NULL, sort_thread, &data[i]);
    }

   
    for (int i = 0; i < num_algos; i++) {
        pthread_join(threads[i], NULL);
    }

    bubble_sort(arr, n);
    printf("\nFinal sorted array (Bubble Sort reference): ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    free(arr);
    return 0;
}
