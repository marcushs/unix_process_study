#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int argc, char **argv)
{
	int	fd[3][2];//3 pipes
	
	for (int i = 0; i < 3; i++)
	{
		if (pipe(fd[i]) == -1)
			return (1);//not the most secure, if one of the pipe call fails but the other worked, need to close all the fds
	}

	int	pid1 = fork();
	if (pid1 == -1)
		return (2);//close before quit
	if (pid1 == 0)
	{
		close(fd[0][1]);
		close(fd[1][0]);
		close(fd[2][0]);
		close(fd[2][1]);
		int	x;
		if (read(fd[0][0], &x, sizeof(int)) == -1)
			return (3);
		x += 5;
		if (write(fd[1][1], &x, sizeof(int)) == -1)
			return (4);
		close(fd[0][0]);
		close(fd[1][1]);
		return (0);
	}
	int	pid2 = fork();
	if (pid2 == -1)
		return (5);
	if (pid2 == 0)
	{
		close(fd[0][0]);
		close(fd[0][1]);
		close(fd[1][1]);
		close(fd[2][0]);
		int	x;
		if (read(fd[1][0], &x, sizeof(int)) == -1)
			return (6);
		x += 5;
		if (write(fd[2][1], &x, sizeof(int)) == -1)
			return (7);
		close(fd[1][0]);
		close(fd[2][1]);
		return (0);
	}
	close(fd[0][0]);
	close(fd[1][0]);
	close(fd[1][1]);
	close(fd[2][1]);
	int	x;
	printf("Input a number here: ");
	scanf("%d", &x);
	if (write(fd[0][1], &x, sizeof(int)) == -1)
		return (8);
	if (read(fd[2][0], &x, sizeof(int)) == -1)
		return (9);
	printf("Result is %d\n", x);
	close(fd[0][1]);
	close(fd[2][0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
