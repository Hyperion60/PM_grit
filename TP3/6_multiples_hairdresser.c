#include <err.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>


sem_t wait_client_man, wait_client_woman, mutex_cpt_man, mutex_cpt_woman;
sem_t wait_hair_man, wait_hair_woman;

int nb_client_man = 0, nb_client_woman = 0, nb_client_max = 0, *ret;


int random_usec(int mod)
{
    return abs((rand() * 1000) % (mod * 1000));
}


void *hair_man(void *args)
{
    while (1)
    {
	sleep(2);
	usleep(random_usec(7));
	sem_wait(&mutex_cpt_man);
	sem_wait(&mutex_cpt_woman);
	if (nb_client_man) // Si il y a des hommes on attend le prochain
	{
	    sem_post(&mutex_cpt_man);
	    sem_post(&mutex_cpt_woman);
	    sem_post(&wait_hair_man);
	    printf("\033[0;34mCoiffeur homme:\033[0m Attend un homme\n");
	    sem_wait(&wait_client_man);
	    printf("\033[0;34mCoiffeur homme:\033[0m Entrain de coiffer un homme\n");
	    sem_wait(&mutex_cpt_man);
	    nb_client_man--;
	    sem_post(&mutex_cpt_man);
	}
	else
	{
	    if (nb_client_woman) // S'il n'y a pas d'hommes mais des femmes 
		    		 // on prend la prochaine
	    {
	        sem_post(&mutex_cpt_man);
		sem_post(&mutex_cpt_woman);
		sem_post(&wait_hair_woman);
	        printf("\033[0;34mCoiffeur homme:\033[0m Attend une femme\n");
		sem_wait(&wait_client_woman);
		printf("\033[0;34mCoiffeur homme:\033[0m Entrain de coiffer une femme\n");
		sem_wait(&mutex_cpt_woman);
		nb_client_woman--;
		sem_post(&mutex_cpt_woman);
	    }
	    else // S'il n'y a ni hommes ni femmes on attend le prochain.
	    {
		sem_post(&mutex_cpt_man);
		sem_post(&mutex_cpt_woman);
		sem_post(&wait_hair_man);
	        printf("\033[0;34mCoiffeur homme:\033[0m Attend un homme\n");
	        sem_wait(&wait_client_man);
		printf("\033[0;34mCoiffeur homme:\033[0m Entrain de coiffer un homme\n");
		sem_wait(&mutex_cpt_man);
		nb_client_man--;
		sem_post(&mutex_cpt_man);
	    }

	}
    }
}


void *hair_woman(void *args)
{
    while (1)
    {
	sleep(2);
	usleep(random_usec(7));
	sem_wait(&mutex_cpt_man);
	sem_wait(&mutex_cpt_woman);
	if (nb_client_woman) // S'il y a des femmes on attend la suivante
	{
	    sem_post(&mutex_cpt_man);
	    sem_post(&mutex_cpt_woman);
	    sem_post(&wait_hair_woman); // On ajoute une place pour une femme
	    printf("\033[0;31mCoiffeur femme:\033[0m Attend une femme\n");
	    sem_wait(&wait_client_woman);
	    printf("\033[0;31mCoiffeur femme:\033[0m Entrain de coiffer une femme\n");
	    sem_wait(&mutex_cpt_woman);
	    nb_client_woman--;
	    sem_post(&mutex_cpt_woman);
	}
	else
	{
	    if (nb_client_man)  // S'il n'y a pas de femmes mais des hommes
		    		// on prend le suivant
	    {
	        sem_post(&mutex_cpt_man);
		sem_post(&mutex_cpt_woman);
		sem_post(&wait_hair_man);
	        printf("\033[0;31mCoiffeur femme:\033[0m Attend un homme\n");
		sem_wait(&wait_client_man);
		printf("\033[0;31mCoiffeur femme:\033[0m Entrain de coiffer un homme\n");
		sem_wait(&mutex_cpt_man);
		nb_client_man--;
		sem_post(&mutex_cpt_man);
	    }
	    else  // S'il n'y a ni hommes ni femmes on attend la suivante
	    {
		sem_post(&mutex_cpt_man);
		sem_post(&mutex_cpt_woman);
		sem_post(&wait_hair_woman);
	        printf("\033[0;31mCoiffeur femme:\033[0m Attend une femme\n");
	        sem_wait(&wait_client_woman);
		printf("\033[0;31mCoiffeur femme:\033[0m Entrain de coiffer une femme\n");
		sem_wait(&mutex_cpt_woman);
		nb_client_woman--;
		sem_post(&mutex_cpt_woman);
	    }

	}
    }
}


void *client_man(void *args)
{
    sem_wait(&mutex_cpt_man);
    if (nb_client_man > nb_client_max) // Plus de place
    {
        printf("\033[0;36mClient homme:\033[0m Plus de place !\n");
	sem_post(&mutex_cpt_man);
	return ret;
    }
    nb_client_man++; // On augmente la file d'hommes
    printf("Nombre de client Homme %d/%d\n", nb_client_man, nb_client_max);
    sem_post(&mutex_cpt_man);
    sem_post(&wait_client_man);
    sem_wait(&wait_hair_man); // On attend la prochaine place pour les hommes
    printf("\033[0;36mClient homme:\033[0m Je me fais coiffer (tid: %ld)\n", pthread_self());
}


void *client_woman(void *args)
{
    sem_wait(&mutex_cpt_woman);
    if (nb_client_woman > nb_client_max)
    {
        printf("\033[0;35mCliente femme:\033[0m Plus de place\n");
	sem_post(&mutex_cpt_woman);
	return ret;
    }
    nb_client_woman++;
    printf("Nombre de cliente Femme %d/%d\n", nb_client_woman, nb_client_max);
    sem_post(&mutex_cpt_woman);
    sem_post(&wait_client_woman);
    sem_wait(&wait_hair_woman); // On attend la prochaine place pour les femmes
    printf("\033[0;35mCliente femme:\033[0m Je me fais coiffer (tid: %ld)\n", pthread_self());
}


int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Usage: %s <nb of client max>\n", argv[0]);
	return 1;
    }

    srand(time(NULL));
    nb_client_max = atoi(argv[1]);


    pthread_t thr_client_man, thr_client_woman, thr_hair_man, thr_hair_woman;

    sem_post(&mutex_cpt_man);
    sem_post(&mutex_cpt_woman);

    int e = pthread_create(&thr_hair_man, NULL, hair_man, NULL);
    if (e != 0)
	errx(EXIT_FAILURE, "pthread_create() failed");


    e = pthread_create(&thr_hair_woman, NULL, hair_woman, NULL);
    if (e != 0)
	errx(EXIT_FAILURE, "pthread_create() failed");


    sem_wait(&wait_hair_man);
    sem_wait(&wait_hair_woman);
    sem_post(&wait_hair_man);
    sem_post(&wait_hair_woman);


    while (1)
    {
        sleep(1);
	if (rand() % 2)
	{
	    printf("Main: Nouveau client Homme\n");
	    e = pthread_create(&thr_client_man, NULL, client_man, NULL);
	    if (e != 0)
		errx(EXIT_FAILURE, "pthread_create() failed");
	}
	else
	{
	    printf("Main: Nouvelle cliente Femme\n");
	    e = pthread_create(&thr_client_woman, NULL, client_woman, NULL);
	    if (e != 0)
		errx(EXIT_FAILURE, "pthread_create() failed");
	}
    }
}
