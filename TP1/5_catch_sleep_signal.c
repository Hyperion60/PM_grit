#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>


static int loop = 1;


void fonc(int sign)
{
    printf("%d\n", sign);
}


void fonc1(int sign)
{
    printf("Numero du signal: %d\n", sign);
    system("who");
}

void fonc2(int sign)
{
    printf("J'ai recu le signal");
    system("df .");
}



int main(void) {
    printf("PID: %d\n", getpid());
    if (signal(SIGHUP, fonc) == SIG_ERR)
        return 1;
    if (signal(SIGINT, fonc) == SIG_ERR)
        return 2;
    if (signal(SIGQUIT, fonc) == SIG_ERR)
        return 3;
    if (signal(SIGILL, fonc) == SIG_ERR)
        return 4;
    if (signal(SIGTRAP, fonc) == SIG_ERR)
        return 5;
    if (signal(SIGABRT, fonc) == SIG_ERR)
        return 6;
    if (signal(SIGIOT, fonc) == SIG_ERR)
        return 7;
    if (signal(SIGBUS, fonc) == SIG_ERR)
        return 8;
    if (signal(SIGFPE, fonc) == SIG_ERR)
        return 9;
    if (signal(SIGSEGV, fonc) == SIG_ERR)
        return 12;
    if (signal(SIGPIPE, fonc) == SIG_ERR)
        return 14;
    if (signal(SIGALRM, fonc) == SIG_ERR)
        return 15;
    if (signal(SIGTERM, fonc) == SIG_ERR)
        return 16;
    if (signal(SIGSTKFLT, fonc) == SIG_ERR)
        return 17;
    if (signal(SIGCHLD, fonc) == SIG_ERR)
        return 18;
    if (signal(SIGCONT, fonc) == SIG_ERR)
        return 19;
    if (signal(SIGTSTP, fonc) == SIG_ERR)
        return 21;
    if (signal(SIGTTIN, fonc) == SIG_ERR)
        return 22;
    if (signal(SIGTTOU, fonc) == SIG_ERR)
        return 23;
    if (signal(SIGURG, fonc) == SIG_ERR)
        return 24;
    if (signal(SIGXCPU, fonc) == SIG_ERR)
        return 25;
    if (signal(SIGXFSZ, fonc) == SIG_ERR)
        return 26;
    if (signal(SIGVTALRM, fonc) == SIG_ERR)
        return 27;
    if (signal(SIGPROF, fonc) == SIG_ERR)
        return 28;
    if (signal(SIGWINCH, fonc) == SIG_ERR)
        return 29;
    if (signal(SIGIO, fonc) == SIG_ERR)
        return 30;
    if (signal(SIGPOLL, fonc) == SIG_ERR)
        return 31;
    if (signal(SIGPWR, fonc) == SIG_ERR)
        return 32;
    if (signal(SIGSYS, fonc) == SIG_ERR)
        return 33;

    if (signal(SIGUSR1, fonc1) == SIG_ERR)
	return 11;
    if (signal(SIGUSR2, fonc2) == SIG_ERR)
	return 13;

    while (loop)
    {
        sleep(10);
    	printf("je dors\n");
    }
    return 0;
}
