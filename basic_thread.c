#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

void *thread(void *argp);

int main() {
    /*

        APLICAÇÃO BÁSICA DE THREADS, SÓ CRIA UMA NOVA THREAD E JOGA UM TEXTO PARA A THREAD CRIADA

    */
    // Tipo abstrato de dados pthread_t
    pthread_t tid;

    printf("Teste com PThreads\n");

    pthread_create(&tid, NULL, thread, NULL);
    pthread_join(tid, NULL);
    pthread_exit((void *)NULL);
}

void *thread(void *argp) {
    printf("Inside the thread action constructor \n");
}
