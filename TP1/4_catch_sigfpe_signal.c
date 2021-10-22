#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>


static int loop = 1;


void traite_fpe(int sign)
{
    printf("Détection d'une erreur.\n");
}


void fonc(int sign)
{
    printf("Numero du signal: %d\n", sign);
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
    if (signal(SIGFPE, traite_fpe) == SIG_ERR)
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

    if (signal(SIGUSR1, fonc) == SIG_ERR)
	return 11;
    if (signal(SIGUSR2, fonc) == SIG_ERR)
	return 13;

    while (loop)
    {
        sleep(1);
	printf("Attention à la division par zéro !\n");
    	float f = 1 / 0;
    }
    return 0;
}
