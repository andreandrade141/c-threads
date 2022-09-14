#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

typedef struct
{ //
    int id;
} thread_arg;

void *thread(void *argp);
pthread_mutex_t mutex; // Estrutura de dados para o mutex "Fechadura"
pthread_cond_t cond;   // Estrutura de dados para o semaforo

int main()
{
    /*

        Demonstra o uso de Semaforos para sincronizar threads.

    */
    int n_threads = 10;       // configura o numero de threads concorrentes do programa
    pthread_t tid[n_threads]; // Dado do tipo pthread_t -> tid[n de threads]
    thread_arg a[n_threads];  // Dado do tipo therad_arg -> a[n de threads]
    int i = 0;

    printf("Starting main program!!!!\n");

    // Inicializa o Lock
    pthread_mutex_init(&mutex, NULL); // inicializa o lock passando o endereço de memória.

    // Inicializa o Semafore
    pthread_cond_init(&cond, NULL); // inicializa o semafore passando o endereço de memória.

    // Criação de Threads
    for (i = 0; i < n_threads; i++)
    {
        a[i].id = i;
        pthread_create(&(tid[i]), NULL, thread, (void *)&(a[i])); // arg[1]: aponta para o endereço onde o tid[i] está.
    }
    // Faz com que o processo pai espere que a thread encerre para acessar o recurso.
    for (i = 0; i < n_threads; i++)
    {
        pthread_join(tid[i], NULL);
    }

    // Elimina o lock, semafore e threads
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    pthread_exit((void *)NULL);
}

void *thread(void *argp)
{
    /*
        Converte a estrutura recebida
    */
    thread_arg *a = (thread_arg *)argp;
    if (a->id == 0)
    {
        // pthread_mutex_lock(&mutex);
        printf("Thread %d: Locking the mutex\n", a->id);
        pthread_cond_wait(&cond, &mutex);
        pthread_mutex_lock(&mutex);
        printf("Thread %d: Unlocking the mutex, clearing up the resource...\n", a->id);
    }
    else
    {
        sleep(2);
        printf("Thread %d: Signaling mutex use...\n", a->id);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
    }
    pthread_exit((void *)NULL);
}
