#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int argc, char **argv)
{
	int	arr[] = {13, 22, 37, 42, 110, 2, 57}; //we have an array of int and we want the sum of them, first we divide the array into 2 arrays and each process calculate one part.
	int	fd[2];
	if (pipe(fd) == -1)
	{
		printf("Error occured when opening pipe!\n");
		return (1);
	}
	int	size = sizeof(arr) / sizeof(int);
	int id = fork();
	if (id == -1)
	{
		printf("Error occured when forking process!\n");
		return (2);
	}
	if (id == 0)
	{
		close(fd[0]);
		int sum = 0;
		for (int i = 0; i < size / 2; i++)
			sum = sum + arr[i];
		printf("The sum from the child process is: %d\n", sum);
		if (write(fd[1], &sum, sizeof(int)) == -1)
		{
			printf("Error occured when writing!\n");
			return (3);
		}
		close(fd[1]);
	}
	else
	{
		wait(NULL);//to ensure we wait for the child process to terminate before executing the parent process
		close(fd[1]);
		int	sumParent = 0;
		int sumChild;
		for (int i = size / 2; i < size; i++)
			sumParent = sumParent + arr[i];
		printf("The sum from the parent process is: %d\n", sumParent);
		if (read(fd[0], &sumChild, sizeof(int)) == -1)
		{
			printf("Error occured when reading!\n");
			return (4);
		}
		printf("The total of the whole array is: %d\n", sumChild + sumParent);
		close(fd[0]);
	}
	return (0);
}
