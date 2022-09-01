#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct{
    int id;
} thread_arg;


void *thread(void *argp);

int main(){
    /*

        Cria n threads concorrentes para executarem operações.

    */
    int n_threads = 10; // configura o numero de threads concorrentes do programa
    pthread_t tid[n_threads];
    thread_arg a[2];
    int i = 0;

    printf("Starting main program!!!!\n");

    // Criação de Threads
    for(i=0; i<n_threads;i++) {
        a[i].id = i;
        pthread_create(&(tid[i]), NULL, thread, (void *)&(a[i]));// arg[1]: aponta para o endereço onde o tid[i] está.

    }
    for(i=0; i<n_threads;i++) {
        pthread_join(tid[i], NULL);
    }

    // Eliminar as Threads
    pthread_exit((void *)NULL);

}

void *thread(void *argp){
    int i = 0;
    thread_arg *a = (thread_arg *)argp;

    printf("Started Thread %d!!!!!\n", a->id);

    for (i=0; i<100000; i++) {};
    printf("Thread %d has ended it's task\n", a->id);
    pthread_exit((void *)NULL);
}
