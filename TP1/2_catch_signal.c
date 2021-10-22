#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>


static int loop = 1;


void sig_handler(int sign)
{
    printf("received %s\n", strsignal(sign));
}


int main(void) {
    if (signal(SIGHUP, sig_handler) == SIG_ERR)
        return 1;
    if (signal(SIGINT, sig_handler) == SIG_ERR)
        return 2;
    if (signal(SIGQUIT, sig_handler) == SIG_ERR)
        return 3;
    if (signal(SIGILL, sig_handler) == SIG_ERR)
        return 4;
    if (signal(SIGTRAP, sig_handler) == SIG_ERR)
        return 5;
    if (signal(SIGABRT, sig_handler) == SIG_ERR)
        return 6;
    if (signal(SIGIOT, sig_handler) == SIG_ERR)
        return 7;
    if (signal(SIGBUS, sig_handler) == SIG_ERR)
        return 8;
    if (signal(SIGFPE, sig_handler) == SIG_ERR)
        return 9;
    // if (signal(SIGKILL, sig_handler) == SIG_ERR)
    //     return 10;
    if (signal(SIGUSR1, sig_handler) == SIG_ERR)
        return 11;
    if (signal(SIGSEGV, sig_handler) == SIG_ERR)
        return 12;
    if (signal(SIGUSR2, sig_handler) == SIG_ERR)
        return 13;
    if (signal(SIGPIPE, sig_handler) == SIG_ERR)
        return 14;
    if (signal(SIGALRM, sig_handler) == SIG_ERR)
        return 15;
    if (signal(SIGTERM, sig_handler) == SIG_ERR)
        return 16;
    if (signal(SIGSTKFLT, sig_handler) == SIG_ERR)
        return 17;
    if (signal(SIGCHLD, sig_handler) == SIG_ERR)
        return 18;
    if (signal(SIGCONT, sig_handler) == SIG_ERR)
        return 19;
    // if (signal(SIGSTOP, sig_handler) == SIG_ERR)
    //     return 20;
    if (signal(SIGTSTP, sig_handler) == SIG_ERR)
        return 21;
    if (signal(SIGTTIN, sig_handler) == SIG_ERR)
        return 22;
    if (signal(SIGTTOU, sig_handler) == SIG_ERR)
        return 23;
    if (signal(SIGURG, sig_handler) == SIG_ERR)
        return 24;
    if (signal(SIGXCPU, sig_handler) == SIG_ERR)
        return 25;
    if (signal(SIGXFSZ, sig_handler) == SIG_ERR)
        return 26;
    if (signal(SIGVTALRM, sig_handler) == SIG_ERR)
        return 27;
    if (signal(SIGPROF, sig_handler) == SIG_ERR)
        return 28;
    if (signal(SIGWINCH, sig_handler) == SIG_ERR)
        return 29;
    if (signal(SIGIO, sig_handler) == SIG_ERR)
        return 30;
    if (signal(SIGPOLL, sig_handler) == SIG_ERR)
        return 31;
    if (signal(SIGPWR, sig_handler) == SIG_ERR)
        return 32;
    if (signal(SIGSYS, sig_handler) == SIG_ERR)
        return 33;

    while (loop)
        sleep(1);

    return 0;
}
