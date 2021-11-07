#include <err.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>


sem_t wait_client, wait_hair, mutex_cpt;
int nb_client = 0, nb_client_max = 0, *ret;

int random_usec(int mod)
{
     return abs((rand() * 1000) % (mod * 1000));
}


void *hair(void *args)
{
    while (1)
    {
	printf("Coiffeur: J'attend\n");
	sleep(2);
	usleep(random_usec(7));
	sem_wait(&wait_client); // On attend le prochain client
	printf("Coiffeur: Entrain de coiffer\n");
	sem_post(&wait_hair); // On libere la place
    }
}


void *client(void *args)
{
    sem_wait(&mutex_cpt);
    if (nb_client > nb_client_max) // Plus de place
    {
	printf("Client: Plus de place !\n");
	sem_post(&mutex_cpt);
	return ret;
    }
    nb_client++; // On ajoute le client au compteur
    printf("Client: Nombre de client dans la file: %d\n", nb_client);
    sem_post(&mutex_cpt);
    sem_post(&wait_client); // On ajoute le client dans le semaphore
    sem_wait(&wait_hair); // On attend la place de coiffeur
    printf("Client: Je me fais coiffer (tid: %ld)\n", pthread_self());
    sem_wait(&mutex_cpt);
    nb_client--; // On decremente le client du compteur
    sem_post(&mutex_cpt);
}


int main(int argc, char **argv)
{
    if (argc == 1)
    {
	printf("Usage: %s <nb of client max>\n", argv[0]);
	return 1;
    }	

    srand(time(NULL));
    nb_client_max = atoi(argv[1]);

    pthread_t thr_client, thr_hair;

    sem_post(&wait_hair);
    sem_post(&mutex_cpt);
    // Creation du coiffeur
    int e = pthread_create(&thr_hair, NULL, hair, NULL);
    if (e != 0)
	errx(EXIT_FAILURE, "pthread_create() failed");


    while (1) // Creation des clients
    {
	sleep(1);
	usleep(random_usec(5));
	printf("Main: Nouveau client \n");
	e = pthread_create(&thr_client, NULL, client, NULL);
	if (e != 0)
	    errx(EXIT_FAILURE, "pthread_create() failed");
	usleep(random_usec(5));
    }
}
