#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define NUM_THREADS 16 // Defina o número de threads desejado
#define NUM_ELEMENTS 128 // Defina o número de elementos no vetor de entrada

void *threadFunc(void *arg) {
    int *num = (int *)arg;
    int diff = num[0] - num[1];
    printf("Diferenca: %d\n", diff);
    pthread_exit(NULL);
}

int main() {
    int input[NUM_ELEMENTS] = {10, 5, 8, 2, 7, 9, 15, 12, 3, 6, 11, 4, 1, 10, 7, 3, 10, 5, 8, 2, 7, 9, 15, 12, 3, 6, 11, 4, 1, 10, 7, 3, 10, 5, 8, 2, 7, 9, 15, 12, 3, 6, 11, 4, 1, 10, 7, 3, 10, 5, 8, 2, 7, 9, 15, 12, 3, 6, 11, 4, 1, 10, 7, 3, 10, 5, 8, 2, 7, 9, 15, 12, 3, 6, 11, 4, 1, 10, 7, 3, 10, 5, 8, 2, 7, 9, 15, 12, 3, 6, 11, 4, 1, 10, 7, 3, 10, 5, 8, 2, 7, 9, 15, 12, 3, 6, 11, 4, 1, 10, 7, 3, 10, 5, 8, 2, 7, 9, 15, 12, 3, 6, 11, 4, 1, 10, 7, 3}; // Vetor de números de entrada
    pthread_t threads[NUM_THREADS];
    int i;

    // Criar as threads
    clock_t start = clock();
    for (i = 0; i < NUM_ELEMENTS; i += 2) {
        int *num = malloc(sizeof(int) * 2);
        num[0] = input[i];
        num[1] = input[i + 1];
        //printf("Thread %d iniciado\n", i % NUM_THREADS);
        pthread_create(&threads[i % NUM_THREADS], NULL, threadFunc, (void *)num);
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
