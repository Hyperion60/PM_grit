#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>


struct arg {
    int num;
    int ret;
};


void *my_thread(void *arg)
{
    int *num = arg;
    float d_time = (rand() / RAND_MAX) % 2000;
    usleep(d_time);
    printf("Thread %d PID: %d\n", *num, getpid());
    d_time = (rand() / RAND_MAX) % 2000;
    usleep(d_time);
    pthread_exit(40);
}


int main(void)
{
    int e;
    int num1 = 1, num2 = 2, num3 = 3;
    void *ret;
    pthread_t thr1, thr2, thr3;

    srand(time(NULL));

    printf("Main thread PID: %d\n", getpid());

    e = pthread_create(&thr1, NULL, my_thread, &num1);
    e = pthread_create(&thr2, NULL, my_thread, &num2);
    e = pthread_create(&thr3, NULL, my_thread, &num3);
    
    printf("Waiting for thread 1...\n");
    pthread_join(thr1, &ret);
    printf("Thread 1, exit code: %d\n", ret);
    
    printf("Waiting for thread 2...\n");
    pthread_join(thr2, &ret);
    printf("Thread 2, exit code: %d\n", ret);
    
    printf("Waiting for thread 3...\n");
    pthread_join(thr3, &ret);
    printf("Thread 3, exit code: %d\n", ret);

    return 0;
}

