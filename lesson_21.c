#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int	main(int argc, char **argv)
{
	int	fd[2];
	if (pipe(fd) == -1)
		return (2);
	int	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		//child process
		close(fd[0]);
		int	n;
		int	arr[10];
		srand(time(NULL));//make sure the sequence of the random numbers is different everytime as we using the actual time to seed the random numbers
		n = rand() % 10 + 1;//we will get a number between 1 to 10
		printf("Generated: \n");
		for (int i = 0; i < n; i++)
		{
			arr[i] = rand() % 11;//number between 0 and 10 inclusive
			printf("%d ", arr[i]);
		}
		printf("\n");
		if (write(fd[1], &n, sizeof(int)) == -1)
			return (4);
		printf("Sent n = %d\n", n);
		if (write(fd[1], arr, sizeof(int) * n) == -1)
			return (3);
		close(fd[1]);
	}
	else
	{
		//parent process
		close(fd[1]);
		int	n;
		int	arr[10];
		int	sum = 0;
		if (read(fd[0], &n, sizeof(int)) == -1)
			return (5);
		printf("Received n = %d\n", n);
		if (read(fd[0], arr, sizeof(int) * n) == -1)
			return (6);
		printf("Received array\n");
		for (int i = 0; i < n; i++)
			sum += arr[i];
		printf("Result is: %d\n", sum);
		close(fd[0]);
		wait(NULL);
	}
	return (0);
}
