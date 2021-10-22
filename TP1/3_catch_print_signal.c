#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>


static int loop = 1;


void traite_sig(int sign)
{
    printf("Fonction Traite_Sig : j'ai recu le signal %s\n", strsignal(sign));
}


int main(void) {
    if (signal(SIGHUP, traite_sig) == SIG_ERR)
        return 1;
    if (signal(SIGINT, traite_sig) == SIG_ERR)
        return 2;
    if (signal(SIGQUIT, traite_sig) == SIG_ERR)
        return 3;
    if (signal(SIGILL, traite_sig) == SIG_ERR)
        return 4;
    if (signal(SIGTRAP, traite_sig) == SIG_ERR)
        return 5;
    if (signal(SIGABRT, traite_sig) == SIG_ERR)
        return 6;
    if (signal(SIGIOT, traite_sig) == SIG_ERR)
        return 7;
    if (signal(SIGBUS, traite_sig) == SIG_ERR)
        return 8;
    if (signal(SIGFPE, traite_sig) == SIG_ERR)
        return 9;
    // if (signal(SIGKILL, traite_sig) == SIG_ERR)
    //     return 10;
    if (signal(SIGUSR1, traite_sig) == SIG_ERR)
        return 11;
    if (signal(SIGSEGV, traite_sig) == SIG_ERR)
        return 12;
    if (signal(SIGUSR2, traite_sig) == SIG_ERR)
        return 13;
    if (signal(SIGPIPE, traite_sig) == SIG_ERR)
        return 14;
    if (signal(SIGALRM, traite_sig) == SIG_ERR)
        return 15;
    if (signal(SIGTERM, traite_sig) == SIG_ERR)
        return 16;
    if (signal(SIGSTKFLT, traite_sig) == SIG_ERR)
        return 17;
    if (signal(SIGCHLD, traite_sig) == SIG_ERR)
        return 18;
    if (signal(SIGCONT, traite_sig) == SIG_ERR)
        return 19;
    // if (signal(SIGSTOP, traite_sig) == SIG_ERR)
    //     return 20;
    if (signal(SIGTSTP, traite_sig) == SIG_ERR)
        return 21;
    if (signal(SIGTTIN, traite_sig) == SIG_ERR)
        return 22;
    if (signal(SIGTTOU, traite_sig) == SIG_ERR)
        return 23;
    if (signal(SIGURG, traite_sig) == SIG_ERR)
        return 24;
    if (signal(SIGXCPU, traite_sig) == SIG_ERR)
        return 25;
    if (signal(SIGXFSZ, traite_sig) == SIG_ERR)
        return 26;
    if (signal(SIGVTALRM, traite_sig) == SIG_ERR)
        return 27;
    if (signal(SIGPROF, traite_sig) == SIG_ERR)
        return 28;
    if (signal(SIGWINCH, traite_sig) == SIG_ERR)
        return 29;
    if (signal(SIGIO, traite_sig) == SIG_ERR)
        return 30;
    if (signal(SIGPOLL, traite_sig) == SIG_ERR)
        return 31;
    if (signal(SIGPWR, traite_sig) == SIG_ERR)
        return 32;
    if (signal(SIGSYS, traite_sig) == SIG_ERR)
        return 33;

    while (loop)
        sleep(1);

    return 0;
}
