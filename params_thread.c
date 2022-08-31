#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>


typedef struct{
    int i;
    int j;
} thread_arg;

void *thread(void *argp);

int main(){
    printf("Starting main thread... \n");

    pthread_t tid;
    thread_arg a;

    a.i = 1;
    a.j = 2;

    pthread_create(&tid, NULL, thread, (void *)&a);
    pthread_join(tid, NULL);
    pthread_exit((void *)NULL);


}


void *thread(void *argp){
    printf("Started new thread...\n");

    thread_arg *a = (thread_arg *) argp; // Cria um ponteiro apontando para a.
    int i = a->i;
    int j = a->j;
    printf("Thread params are: %d and %d!!!!!\n", i, j);
}
