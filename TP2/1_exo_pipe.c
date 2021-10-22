#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(void)
{
    char c, d;
    int Tube[2];
    if (pipe(Tube) == -1)
    {
	perror("pipe");
	exit(EXIT_FAILURE);
    }

    pid_t pid, wpid;
    int status;
    
    pid = fork();

    if (pid == -1)
    {
	perror("fork");
	exit(EXIT_FAILURE);
    }

    if (pid == 0)
    {
	printf("Je suis le fils\n");
	close(Tube[1]); // Close useless space
	
	while (read(Tube[0], &d, 1) > 0) // Read char by char in pipe
	{
	    printf("fils: %c\n", d); // Write char by char in STDOUT
	}
	printf("EOF received\n");
	close(Tube[0]); // Close pipe
	_exit(EXIT_SUCCESS); // Exit son with success
    } 
    else
    {
	close(Tube[0]);
	printf("Je suis le père\n");
	while (scanf(" %c", &c) > 0) // Read char by char in STDIN
	{
	    printf("Pere: %c %x\n", c, c);
	    write(Tube[1], &c, 1); // Write char by char in pipe
	}

	close(Tube[1]);
	wait(NULL);
	printf("Mon fils est mort\n");
	exit(EXIT_SUCCESS);	
    }
}
