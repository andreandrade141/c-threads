#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int id;
} thread_arg;

void *thread(void *argp);
pthread_mutex_t mutex;
int var;


int main() {
    /*

        Demonstra o lock e unlock de multiplas threads usando mutex.

    */
    int n_threads = 10; // configura o numero de threads concorrentes do programa
    pthread_t tid[n_threads];
    thread_arg a[2];
    int i = 0;

    printf("Starting main program!!!!\n");

    // Inicializa o Lock
    pthread_mutex_init(&mutex,NULL);

    // Criação de Threads
    for(i=0; i<n_threads;i++) {
        a[i].id = i;
        pthread_create(&(tid[i]), NULL, thread, (void *)&(a[i]));// arg[1]: aponta para o endereço onde o tid[i] está.

    }

    for(i=0; i<n_threads;i++) {
        pthread_join(tid[i], NULL);
    }

    // Elimina o lock
    pthread_mutex_destroy(&mutex);

    // Eliminar as Threads
    pthread_exit((void *)NULL);

}



void *thread(void *argp){
    /*
        Converte a estrutura recebida
    */
    thread_arg *a = (thread_arg *)argp;
    pthread_mutex_lock(&mutex);
    printf("Thread %d: value before the operation: %d\n", a->id+1, var);
    var = var + a->id + 1;
    printf("Thread %d: value after the operation: %d\n", a->id+1, var);

    pthread_mutex_unlock(&mutex);
    pthread_exit((void *)NULL);
}
