#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//this is my own implementation of the same program before watching the lesson, using 2 pipes and sleep
int	main(int argc, char **argv)
{
	int	fd[2];
	int	x;

	if (pipe(fd) == -1)//create the first pipe for first child
		return (1);
	printf("Input a number: ");
	scanf("%d", &x);
	if (write(fd[1], &x, sizeof(int)) == -1)//write the number got from user to the pipe
		return (2);
	printf("Wrote number %d to the pipe\n", x);
	int	pid1 = fork();
	if (pid1 == -1)
		return (2);
	if (pid1 == 0)
	{
		int	y;
		int	z;
		if (read(fd[0], &y, sizeof(int)) == -1)//read the number from the pipe
			return (3);
		z = y + 5;
		printf("Read number %d from the pipe, %d + 5 = %d\n", y, y, z);
		if (write(fd[1], &z, sizeof(int)) == -1)//write the number + 5 to the pipe
			return (4);
		printf("Wrote number %d to the pipe\n", z);
		close(fd[0]);//close all fds in this process
		close(fd[1]);
	}
	sleep(1);//wait for 1 sec to make sure the child process had the time to finish executing before reading again, otherwise hang
	if (read(fd[0], &x, sizeof(int)) == -1)//read and update the number after calculation then close all fds in this process
		return (9);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL, 0);//wait after closing all the fds, otherwise hang
	int	fd2[2];
	if (pipe(fd2) == -1)//open a second pipe for the second child
		return (11);
	if (write(fd2[1], &x, sizeof(int)) == -1)//write the number to the second pipe, then same thing as above
		return (12);
	int	pid2 = fork();
	if (pid2 == -1)
		return (5);
	if (pid2 == 0)
	{
		int	y;
		int	z;
		if (read(fd2[0], &y, sizeof(int)) == -1)
			return (6);
		z = y + 5;
		printf("Read number %d from the pipe, %d + 5 = %d\n", y, y, z);
		if (write(fd2[1], &z, sizeof(int)) == -1)
			return (7);
		printf("Wrote number %d to the pipe\n", z);
		close(fd2[0]);
		close(fd2[1]);
	}
	sleep(1);
	if (read(fd2[0], &x, sizeof(int)) == -1)
		return (8);
	close(fd2[0]);
	close(fd2[1]);
	waitpid(pid2, NULL, 0);
	printf("The final result is: %d\n", x);
	return (0);
}
