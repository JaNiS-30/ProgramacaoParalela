#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 1 // Defina o número de threads desejado
#define NUM_ELEMENTS 128 // Defina o número de elementos no vetor de entrada

typedef struct {
    int num1;
    int num2;
} ThreadArgs;

int GCD(int m, int n)
{
    if (n==0) return m;
    return GCD(n, m % n);
}

void *threadFunc(void *arg) {
    ThreadArgs *args = (ThreadArgs *)arg;
    int result = GCD(args->num1, args->num2);
    printf("%d\n", result);
    pthread_exit(NULL);
}

int main() {
    int input[NUM_ELEMENTS] = {10, 5, 8, 2, 7, 9, 15, 12, 3, 6, 11, 4, 1, 10, 7, 3, 10, 5, 8, 2, 7, 9, 15, 12, 3, 6, 11, 4, 1, 10, 7, 3, 10, 5, 8, 2, 7, 9, 15, 12, 3, 6, 11, 4, 1, 10, 7, 3, 10, 5, 8, 2, 7, 9, 15, 12, 3, 6, 11, 4, 1, 10, 7, 3, 10, 5, 8, 2, 7, 9, 15, 12, 3, 6, 11, 4, 1, 10, 7, 3, 10, 5, 8, 2, 7, 9, 15, 12, 3, 6, 11, 4, 1, 10, 7, 3, 10, 5, 8, 2, 7, 9, 15, 12, 3, 6, 11, 4, 1, 10, 7, 3, 10, 5, 8, 2, 7, 9, 15, 12, 3, 6, 11, 4, 1, 10, 7, 3};
    pthread_t threads[NUM_THREADS];
    ThreadArgs threadArgs[NUM_THREADS];
    int i;

    // Criar as threads
    clock_t start = clock();
    for (i = 0; i < NUM_ELEMENTS; i += 2) {
        threadArgs[i % NUM_THREADS].num1 = input[i];
        threadArgs[i % NUM_THREADS].num2 = input[i + 1];
        pthread_create(&threads[i % NUM_THREADS], NULL, threadFunc, (void *)&threadArgs[i % NUM_THREADS]);
    }

    // Aguardar a conclusão de todas as threads
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }
    clock_t end = clock();

    double elapsedTime = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Tempo de execução: %.6f segundos\n", elapsedTime);

    return 0;
}
