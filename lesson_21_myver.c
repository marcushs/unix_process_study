#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <time.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

// create 2 processes
// 1) Child process should generate random numbers and send them to the parent
// 2) Parent receive and sum them all up and print the result
//This is my version of the exercise, my program prompt the user for the size of the array, then I generate random numbers, write to the fifo file, parent process reads the array and does the calculation

int	main(int argc, char **argv)
{
	if (mkfifo("fifo", 0777) == -1)//create the fifo file, if the file already exist, the program exit, so rm fifo before executing
		return (1);
	int	pid = fork();//create child process
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		//child process
		int fd_1 = open("fifo", O_WRONLY);//open writing end of fifo
		int	x;
		int	*arr;
		srand(time(NULL));
		printf("Input the size of the array: ");
		scanf("%d", &x);
		if (write(fd_1, &x, sizeof(int)) == -1)//write the size of array to the fifo so that the parent process know how many elements are there, in order to malloc
		{
			close(fd_1);
			exit(EXIT_FAILURE);
		}
		printf("Wrote array size to pipe: %d\n", x);
		arr = (int *)malloc(sizeof(int) * x);
		if (!arr)
		{
			close(fd_1);
			exit(EXIT_FAILURE);
		}
		for (int i = 0; i < x; i++)
			arr[i] = rand() % 100;//fill the array with random numbers
		if (write(fd_1, arr, sizeof(int) * x) == -1)//write the array to fifo
		{
			close(fd_1);
			free(arr);
			arr = NULL;
			exit(EXIT_FAILURE);
		}
		printf("Wrote array to pipe!\n");
		for (int i = 0; i < x; i++)
			printf("%d\n", arr[i]);
		close(fd_1);
		free(arr);
		arr = NULL;
		exit(EXIT_SUCCESS);
	}
	else
	{
		int fd_0 = open("fifo", O_RDONLY);//directly open reading end as well, otherwise the program will block as fifo needs to be opened at both end in order to continue to execute
		//parent process
		int	wstatus;
		waitpid(pid, &wstatus, 0);
		if (WIFEXITED(wstatus))//we wait for the child process and see if the process exited with success status code
		{
			if(WEXITSTATUS(wstatus) == EXIT_FAILURE)// if not we quit
			{
				close(fd_0);
				exit(EXIT_SUCCESS);
			}
			else
			{
				int	y;
				int	*arr;
				int	sum = 0;
				if (read(fd_0, &y, sizeof(int)) == -1)
				{
					printf("read failed\n");
					close(fd_0);
					exit(EXIT_FAILURE);
				}
				printf("Received array size from child process: %d\n", y);
				arr = (int *)malloc(sizeof(int) * y);
				if (!arr)
				{
					close(fd_0);
					exit(EXIT_FAILURE);
				}
				if (read(fd_0, arr, sizeof(int) * y) == -1)//be careful we pass in arr not &arr to read, arr is already a pointer
				{
					close(fd_0);
					free(arr);
					arr = NULL;
					exit(EXIT_FAILURE);
				}
				printf("Received array from the child process!\n");
				for (int i = 0; i < y; i++)
					printf("%d\n", arr[i]);
				for (int i = 0; i < y; i++)
					sum += arr[i];
				printf("Calculated the sum of the array in parent process: %d\n", sum);
				close(fd_0);
				free(arr);
				arr = NULL;
			}
		}
	}
	return (0);
}

//Note regarding FIFO

/* Once both ends of a named pipe have been opened, it is possible to close one end and continue using the other end. In fact, it is common for one process to close its end of the pipe after it has finished writing data, and for the other process to close its end of the pipe after it has finished reading data.

Closing an end of the pipe signals to the other process that no more data will be written or read on that end. The other process can then detect this by receiving an end-of-file (EOF) indication when it tries to read from the pipe, or by getting a write error when it tries to write to the pipe.

So, in your case, if the child process has finished writing data and closed its end of the pipe, the parent process can still read the data that was written before the child process closed the pipe. When the parent process tries to read from the pipe after the child process has closed it, it will receive an EOF indication, indicating that no more data will be available from the pipe. The parent process can then close its end of the pipe and exit the program.*/
