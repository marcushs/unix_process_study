#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int argc, char **argv)
{
	int	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
		execlp("ping", "ping", "-c", "3", "google.com", NULL);
	else
	{
		wait(NULL);
		printf("Success!\n");
	}
	return (0);
}
