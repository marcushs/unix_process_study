#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		// int	file = open("pingResult.txt", O_WRONLY | O_CREAT, 0777);
		// if (file == -1)
		// 	return (2);
		// int	file2 = dup2(file, STDOUT_FILENO);
		// close(file);
		int err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
		if (err == -1)
		{
			printf("Command not found!\n");
			return (err);
		}
	}
	else
	{
		int	wstatus;
		wait(&wstatus);
		//printf("%d\n", wstatus); I got 65280 here
		if (WIFEXITED(wstatus))
		{
			int	statusCode = WEXITSTATUS(wstatus);
			if (statusCode == 0)
				printf("Success!\n");
			else
				printf("Failure with exit status code: %d!\n", statusCode);
		}
		printf("Some post processing goes here!\n");
	}
	return (0);
}
