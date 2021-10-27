#include <err.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>


static int nb_client, nb_client_max;
sem_t wait_client = 0, wait_hair = 1, mutex_cpt = 1;



void *hair(void *args)
{
    while (1)
    {
	sem_wait(&wait_client);
	printf("Coiffeur: Entrain de coiffer\n");
	sem_post(&wait_hair);
    }
}


void *client(void *args)
{
    sem_wait(&mutex_cpt);
    if (nb_client > nb_client_max)
    {
	sem_post(&mutex_cpt);
	return EXIT_FAILURE;
    }
    nb_client++;
    sem_post(&mutex_cpt);
    sem_post(&wait_client);
    sem_wait(&wait_hair);
    printf("Client: Je me fais coiffer (tid: %d\n", pthread_self());
    sem_wait(&mutex_cpt);
    nb_client--;
    sem_post(&mutex_cpt);
    return EXIT_SUCCESS;
}

/*
void *client(void *args)
{
    struct arg_client *arg = args
    struct queue *_queue = args->_queue;
    sem_wait(&mutex_cpt);
    if (nb_client > nb_client_max)
    {
	sem_post(&mutex_cpt);
	disable_client(arg->_queue, arg->
	return EXIT_FAILURE;
    }
    nb_client++;
    sem_post(&mutex_cpt);
}
*/

int main(int argc, char **argv)
{
    if (argc == 1)
	printf("Usage: %s <nb of client max>\n", argv[0]);

    nb_client_max = atoi(argv[1]);

    int thr_client, thr_hair;

    struct queue *clients_queue = new_queue();

    int e = pthread_create(&thr_client, NULL, client, NULL);
    if (e != 0)
	errx(EXIT_FAILURE, "pthread_create() failed");

    e = pthread_create(&thr_hair, NULL, hair, NULL);
    if (e != 0)
	errx(EXIT_FAILURE, "pthread_create() failed");

}
