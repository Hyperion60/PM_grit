#include <err.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define EXIT_FAILURE 1


struct args {
    int a;
    int b;
};


float random_usec(int mod)
{
    return (rand() / RAND_MAX) % (mod * 1000);
}


void *thread1(void *args)
{
    struct args *arguments = args;
    usleep(random_usec(2));
    arguments->a += 1;
    usleep(random_usec(2));
    arguments->b += 1;
    usleep(random_usec(2));
    printf("Thread 1: %d / %d\n", arguments->a, arguments->b);
}


void *thread2(void *args)
{
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
    struct args *arguments = args;
    usleep(random_usec(2));
    arguments->a -= 1;
    usleep(random_usec(2));
    arguments->b -= 1;
    usleep(random_usec(2));
    printf("Thread 3: %d / %d\n", arguments->a, arguments->b);
}


int main(void)
{
    struct args arguments;
    arguments.a = 1;
    arguments.b = 1;
    pthread_t thr1, thr2, thr3;
    int e1, e2, e3;

    srand(time(NULL));

    printf("Main thread PID: %d\n", getpid());

    e1 = pthread_create(&thr1, NULL, thread1, &arguments);
    if (e1 != 0)
	errx(EXIT_FAILURE, "pthread1_create() failed");

    e2 = pthread_create(&thr2, NULL, thread2, &arguments);
    if (e2 != 0)
	errx(EXIT_FAILURE, "pthread2_create() failed");

    e3 = pthread_create(&thr3, NULL, thread3, &arguments);
    if (e3 != 0)
	errx(EXIT_FAILURE, "pthread3_create() failed");

    sleep(2);

    pthread_join(thr1, NULL);
    pthread_join(thr2, NULL);
    pthread_join(thr3, NULL);

    return 0;
}
