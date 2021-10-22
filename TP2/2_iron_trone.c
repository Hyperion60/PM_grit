#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(void)
{
    // God process
    pid_t mb, js, ld, wpid; // Marcheur Blanc, John Snow, living dead
    int first = rand() % 2; // Winner

    int Tube[2]; // pipe between JS and living dead
    int pid, status, mb_location, js_location;
    
    if (pipe(Tube) == -1) // Create pipe
    {
	perror("pipe");
	exit(EXIT_FAILURE);
    }

    mb = fork();

    if (mb == 0) // MB process
    {
	for (int i = 0; i < 10; ++i)
	{
	    close(Tube[0]);
	    ld = fork();
	    if (ld == 0)
	    {
		int myppid = 0;
		int mypid = getpid();
		if (!i)
		    myppid = getppid();
		if (signal(SIGTERM, SIG_IGN))
		    return 42;
		if (!i)
		    write(Tube[1], &(myppid), 1); // Write mb pid in pipe
		write(Tube[1], &(mypid), 1); // Write their pid in pipe
		sleep(2);
		_exit(22);
	    }
	    else
	    {
	        wpid = wait(&status);
		if (wpid != -1)
		    printf("%d : My beautiful living dead is really dead %d :-(\n", i, WEXITSTATUS(status));
	    }
	    sleep(1);
	}
	close(Tube[1]);
	if (first)
	{
	    kill(js_location, SIGTERM);
	    printf("Le marcheur Blanc a gagné!\n");
	}
	_exit(EXIT_SUCCESS);
    }
    else // God process
    {
	js = fork();
	if (js == 0) // JS process
	{
	    js_location = getpid();
	    close(Tube[1]);
	    int nb = 0;
	    while (read(Tube[0], &pid, 1) > 0)
	    {
		sleep(1);
		printf("LV detected: %d\n", pid);
		if (!nb++)
		    mb_location = pid; // First living dead provide mb pid
		else
		    kill(pid, SIGKILL); // kill living dead pid
	    }
	    close(Tube[0]);
	    if (!first) // Random int define at the begin
	    {
		kill(mb_location, SIGKILL);
	    	printf("Jon Snow a gagné!\n");
	    }
	    _exit(EXIT_SUCCESS);
	}
	else
	{
	    wait(NULL);
	}
    }
}
