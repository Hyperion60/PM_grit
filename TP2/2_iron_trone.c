#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>


int main(void)
{
    srand(time(NULL));
    // God process
    pid_t mb, js, ld, wpid; // Marcheur Blanc, John Snow, living dead
    int first = rand() % 2; // Winner

    int Tube[2]; // pipe between JS and living dead
    int pid, status, mb_location, js_location;
    // PIDs: pid (living dead in Pipe), status (exit code of living death)
    // mb_location (Marcheur Blanc get by John Snow from living death)
    // js_location (John Snow PID gives by God to Marcheur Blanc)
    
    if (pipe(Tube) == -1) // Create pipe and check error
    {
	perror("pipe");
	exit(EXIT_FAILURE);
    }

    mb = fork(); // Fork between God and MB

    if (mb == 0) // MB process
    {
	for (int i = 0; i < 10; ++i) // Number of living death
	{
	    close(Tube[0]); // Close useless Pipe case
	    ld = fork(); // Fork foreach living death one by one
	    if (ld == 0) // Living death process
	    {
		int myppid = 0; // MB PID init
		int mypid = getpid(); // Living Death PID
		if (signal(SIGTERM, SIG_IGN)) // Catch dead signal 
		    return 42; // Return the life answer
		if (!i) // If is the first living death
		{
		    myppid = getppid(); // The first living death get the
		       			// MB PID, the condition avoid useless
					// function
		    write(Tube[1], &(myppid), 1); // Write MB PID in pipe
		}
		write(Tube[1], &(mypid), 1); // Write their PID in pipe
		sleep(2); // Sleep to avoid time out (end process)
		_exit(22); // Exit process with another code (debug)
	    }
	    else
	    {
	        wpid = wait(&status); // Waiting the living death dead
		if (wpid != -1) // When lv dead MB print a message before to recreate another (limit: 10)
		    printf("%d : My beautiful living dead is really dead %d :-(\n", i, WEXITSTATUS(status));
	    }
	    sleep(1); // 1 seconde between two lv creation
	}
	close(Tube[1]); // Close pipe when all lv are dead
	if (first) // Random int to decide who kill in first
	{
	    kill(js_location, SIGTERM); // Kill JS with the PID gives by God 
	    printf("Le marcheur Blanc a gagné!\n"); // Celebrate his victory
	}
	sleep(2);
	_exit(EXIT_SUCCESS); // Terminate his life in happy
    }
    else // God process
    {
	js = fork(); // Create JS fork
	if (js == 0) // JS process
	{
	    js_location = getpid(); // God takes the JS PID
	    close(Tube[1]); // Close useless Pipe case
	    int nb = 0; // Count the number of living death
	    while (read(Tube[0], &pid, 1) > 0) // Read the living death PID 
	    {
		sleep(1); // Wait to avoid strange errors
		printf("LV detected: %d\n", pid); // Debug message 
		if (!nb++) // First living death
		    mb_location = pid; // First living dead provide mb pid
		else
		    kill(pid, SIGTERM); // kill living dead pid
	    }
	    close(Tube[0]); // Close Pipe
	    if (!first) // Random int define at the begin
	    {
		kill(mb_location, SIGKILL); // Kill MB with the PID gives by living death
	    	printf("Jon Snow a gagné!\n"); // Celebrate his victory
	    }
	    sleep(2);
	    _exit(EXIT_SUCCESS); // Terminate his life in happy
	}
	else
	{
	    wait(NULL); // God wait all process are terminated before shutdown
	}
    }
    return 0;
}
