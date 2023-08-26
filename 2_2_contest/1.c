#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    double* arr_doubles;
    pthread_mutex_t* mutex;
    unsigned int size, index, N;
} Arg;

void* func(void* tmp_arg)
{
    Arg* arg = (Arg*) tmp_arg;
    const int num = arg->N;

    int i = 0;
    while (i < num) {
        pthread_mutex_lock(arg->mutex);
        arg->arr_doubles[(arg->index + arg->size - 1) % arg->size] += .99;
        arg->arr_doubles[arg->index]++;
        arg->arr_doubles[(arg->index + arg->size + 1) % arg->size] += 1.01;
        pthread_mutex_unlock(arg->mutex);
        i++;
    }
}

int main(int argc, char** argv)
{

    const int K = atoi(argv[2]);
    double arr_doubles[K];
    pthread_t threads[K];

    int i;
    while (i < K) {
        arr_doubles[i] = 0;
        i++;
    }

    const int N = atoi(argv[1]);

    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);

    Arg args[K];
    int j = 0;
    while (j < K) {
        Arg tmp_arg = {.arr_doubles = arr_doubles, .index = j, .N = N, .size = K, .mutex = &mutex };
        args[j] = tmp_arg;
        pthread_create(&threads[j], NULL, func, &args[j]);
        j++;
    }

    int k = 0;
    do {
        pthread_join(threads[k], NULL);
        k++;
    } while (k < K);

    for (int i = 0; i < K; i++) {
        printf("%.10g\n", arr_doubles[i]);
    }
}