#include <err.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define EXIT_FAILURE 1
#define SEMAPHORE 1

sem_t sem1, sem2, sem3;

struct args {
    int a;
    int b;
};


int random_usec(int mod)
{
    return (rand() / RAND_MAX) % (mod * 1000);
}


// Creation des threads avec gestion d'erreur
void thread_create(pthread_t *restrict thr, void *func, void *args)
{
    int e = pthread_create(thr, NULL, func, args);
    if (e != 0)
	errx(EXIT_FAILURE, "pthread_create() failed");
}


void *thread1(void *args)
{
    sem_wait(&sem2);
    struct args *arguments = args;
    usleep(random_usec(2));
    arguments->a += 1;
    usleep(random_usec(2));
    arguments->b += 1;
    usleep(random_usec(2));
    printf("Thread 1: %d / %d\n", arguments->a, arguments->b);
    sem_post(&sem3); // Zone critique du thread 3
    
}


void *thread2(void *args)
{
    sem_wait(&sem3);
    struct args *arguments = args;
    usleep(random_usec(2));
    arguments->a *= 2;
    usleep(random_usec(2));
    arguments->b *= 2;
    usleep(random_usec(2));
    printf("Thread 2: %d / %d\n", arguments->a, arguments->b);
}


void *thread3(void *args)
{
    sem_wait(&sem1);
    struct args *arguments = args;
    usleep(random_usec(2));
    arguments->a -= 1;
    usleep(random_usec(2));
    arguments->b -= 1;
    usleep(random_usec(2));
    printf("Thread 3: %d / %d\n", arguments->a, arguments->b);
    sem_post(&sem2); // Zone critique du thread 2
}


int main(void)
{
    struct args arguments;
    arguments.a = 1;
    arguments.b = 1;
    pthread_t thr1, thr2, thr3;
    int e1, e2, e3;
    sem_post(&sem1); // Zone critique du thread 1
    srand(time(NULL));
    int first = rand() % 3, second = rand() % 2;
    
    printf("Main thread PID: %d\n", getpid());

    if (!first)
    {
	thread_create(&thr1, thread1, &arguments);
	if (second)
	{
	    thread_create(&thr2, thread2, &arguments);
	    thread_create(&thr3, thread3, &arguments);
	}
	else
	{
	    thread_create(&thr3, thread3, &arguments);
	    thread_create(&thr2, thread2, &arguments);
	}
    }
    else if (first == 1)
    {
	thread_create(&thr2, thread2, &arguments);
	if (second)
	{
	    thread_create(&thr1, thread1, &arguments);
	    thread_create(&thr3, thread3, &arguments);
	}
	else
	{
	    thread_create(&thr3, thread3, &arguments);
	    thread_create(&thr1, thread1, &arguments);
	}
    }
    else if (first == 2)
    {
	thread_create(&thr3, thread3, &arguments);
	if (second)
	{
	    thread_create(&thr1, thread1, &arguments);
	    thread_create(&thr2, thread2, &arguments);
	}
	else
	{
	    thread_create(&thr2, thread2, &arguments);
	    thread_create(&thr1, thread1, &arguments);
	}
    }
    // On attend la fin des threads pour arreter le main thread
    pthread_join(thr1, NULL);
    pthread_join(thr2, NULL);
    pthread_join(thr3, NULL);

    return 0;
}
