#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


typedef struct {
    int *fib;   
    int n;      
} FibData;


void* generate_fibonacci(void* arg) {
    FibData *data = (FibData*) arg;

    if (data->n > 0) data->fib[0] = 0;
    if (data->n > 1) data->fib[1] = 1;

    for (int i = 2; i < data->n; i++) {
        data->fib[i] = data->fib[i-1] + data->fib[i-2];
    }

    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <number_of_terms>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    if (n <= 0) {
        printf("Number of terms must be positive.\n");
        return 1;
    }


    int *fib = malloc(n * sizeof(int));
    if (fib == NULL) {
        perror("malloc failed");
        return 1;
    }

    FibData data;
    data.fib = fib;
    data.n = n;

    pthread_t tid;

    pthread_create(&tid, NULL, generate_fibonacci, &data);

    pthread_join(tid, NULL);

    
    printf("Fibonacci series (%d terms):\n", n);
    for (int i = 0; i < n; i++) {
        printf("%d ", fib[i]);
    }
    printf("\n");

    free(fib);
    return 0;
}
