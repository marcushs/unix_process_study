#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int	main(int argc, char **argv)
{
	int	fd[2];
	//fd[0] - read end
	//fd[1] - write end
	if (pipe(fd) == -1)
	{
		printf("An error occured\n");
		return (1);
	}
	int	id = fork();
	if (id == -1)
	{
		printf("Error occured when forking\n");
		return (4);
	}
	if (id == 0)
	{
		//here we close the read end in the child process immediately because we do not need to read from it
		close(fd[0]);
		int	x;
		printf("Input a number: ");
		scanf("%d",  &x);
		if (write(fd[1], &x, sizeof(int)) == -1)
		{
			printf("Error occured when writing to the pipe\n");
			return (2);
		}
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		int	y;
		if (read(fd[0], &y, sizeof(int)) == -1)
		{
			printf("Error occured when reading from the pipe\n");
			return (3);
		}
		close(fd[0]);
		printf("The number from the child process is: %d\n", y);
		wait(NULL);
	}
	return (0);
}
