#include <err.h>
#include <pthread.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

#define EXIT_FAILURE 1


struct args {
    int a;
    int b;
};


void *thread1(void *args)
{
    struct args *arguments = args;
    sleep(1);
    arguments->a += 1;
    sleep(1);
    arguments->b += 1;
    sleep(1);
    printf("Thread 1: %d / %d\n", arguments->a, arguments->b);
}


void *thread2(void *args)
{
    struct args *arguments = args;
    sleep(1);
    arguments->a *= 2;
    sleep(1);
    arguments->b *= 2;
    sleep(1);
    printf("Thread 2: %d / %d\n", arguments->a, arguments->b);
}


void *thread3(void *args)
{
    struct args *arguments = args;
    sleep(1);
    arguments->a -= 1;
    sleep(1);
    arguments->b -= 1;
    sleep(1);
    printf("Thread 3: %d / %d\n", arguments->a, arguments->b);
}


int main(void)
{
    struct args arguments;
    arguments.a = 1;
    arguments.b = 1;
    pthread_t thr1, thr2, thr3;
    int e1, e2, e3;

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

    pthread_join(thr1, NULL);
    pthread_join(thr2, NULL);
    pthread_join(thr3, NULL);

    return 0;
}
