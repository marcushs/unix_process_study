#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <signal.h>

int	main(int argc, char **argv)
{
	int	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		while (1)
		{
			printf("Some text here\n");
			usleep(50000);//50000 microseconds
		}
	}
	else
	{
		sleep(1);//wait 1 second
		kill(pid, SIGKILL);//sends a signal to a process interrupt the target process, whether it is to terminate it or pause the execution
		wait(NULL);
	}
	return (0);
}
