#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(void)
{
    char c, d; // Char c: Write in pipe by parent, char d: Read in pipe by child
    int Tube[2]; // Pipe declaration
    if (pipe(Tube) == -1) // Build pipe with error detection
    {
	perror("pipe");
	exit(EXIT_FAILURE);
    }

    pid_t pid; // PID for fork
    int status; // Status for exit child code
    
    pid = fork(); // Fork

    if (pid == -1) // Detection of fork failure
    {
	perror("fork");
	exit(EXIT_FAILURE);
    }

    if (pid == 0) // Child process
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
    else // Parent process
    {
	close(Tube[0]);
	printf("Je suis le père\n");
	while (scanf(" %c", &c) > 0) // Read char by char in STDIN
	{
	    printf("Pere: %c %x\n", c, c);
	    write(Tube[1], &c, 1); // Write char by char in pipe
	}

	close(Tube[1]);
	wait(NULL); // Wait child terminated
	printf("Mon fils est mort\n");
	exit(EXIT_SUCCESS);	
    }
}
