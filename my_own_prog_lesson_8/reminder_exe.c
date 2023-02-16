#include "reminder_exe.h"

//This is the program that I wrote with knowledge I learnt up until lesson 8
/*This program has 3 processes, the children processes will take in a string(only numbers) from the user,
then split it into 2 halves and calculate the sum of each half in each process, 
finally the parent process will read and print on stdout
*/

int	main (int argc, char **argv)
{
	int	*fd;
	int	id;
	int	id2;

	//malloc an array of size 2 for pipe() call
	fd = (int *)malloc(sizeof(int) * 2);
	if (!fd)
		return (1);

	//open pipe for read and write
	if (pipe(fd) == -1)
	{
		printf("Error opening pipe!\n");
		return (1);
	}

	//just wnated to know what the fds are, 3 and 4 in this case
	// for (int i = 0; fd[i]; i++)
	// 	printf("fd[%d] == %d\n", i, fd[i]);

	//create one child process
	id = fork();
	if (id == -1)
	{
		//if fork() fails, I free the malloced arr fd and print a message, then quit
		printf("Error\n");
		return (free(fd), fd = NULL, 2);
	}
	

	//in the child process
	if (id == 0)
	{
		//I set a string of size 1000 to accomodate the user's input, can't use malloc as we don't know the size in advance
		char str[1000];
		char **strs;
		int		count;
		long	*arr;

		printf("Input numbers here:\n");

		//scanf %[^\n] so that I can take in white spaces in the string
		scanf("%[^\n]", str);

		//Here I just assume that the string will not have more than 1000 char, then split into strs
		strs = ft_split(str, ' ');
		if (!strs)
		{
			//if anything wrong with split, free fd print and exit
			printf("Error occured from ft_split!\n");
			free(fd);
			fd = NULL;
			exit(EXIT_FAILURE);
		}

		//then I check if the char only contains digits, '-', '+', of course '-' and '+' can only be in front of a num
		if (!check_char_strs(strs))
		{
			//if error
			printf("Invalid input!\n");

			//free strs
			for (int i = 0; strs[i]; i++)
			{
				free(strs[i]);
				strs[i] = NULL;
			}
			free(strs);
			strs = NULL;
			exit(EXIT_FAILURE);
		}

		//knowing how many numbers are there
		count = count_elements(strs);

		arr = (long *)malloc(sizeof(long) * count);
		if (!arr)
		{
			//if mallocing arr fails, I free fd and strs, print message and quit
			printf("Error occured when allocating memory!\n");

			//free strs
			for (int i = 0; strs[i]; i++)
			{
				free(strs[i]);
				strs[i] = NULL;
			}
			free(strs);
			strs = NULL;
			exit(EXIT_FAILURE);
		}

		//if everything is alright, then atoi and put into arr (only accepting INT_MIN < n < INT_MAX), arr of long for overflow
		for (int i = 0; i < count; i++)
		{
			long	num;
			num = ft_atoi(strs[i]);
			if (num > 2147483647 || num < -2147483648)
			{
				printf("Input outside of int range!\n");
				//free strs
				for (int i = 0; strs[i]; i++)
				{
					free(strs[i]);
					strs[i] = NULL;
				}
				free(strs);
				strs = NULL;

				//free fd
				free(fd);
				fd = NULL;
				exit(EXIT_FAILURE);
			}
			arr[i] = num;
		}

		//free strs that we no longer need
		for (int i = 0; strs[i]; i++)
		{
			free(strs[i]);
			strs[i] = NULL;
		}
		free(strs);
		strs = NULL;

		//fork again in child process
		id2 = fork();
		if (id2 == -1)
		{
			printf("Error occured when forking process!\n");
			free(fd);
			fd = NULL;
			exit(EXIT_FAILURE);
		}
		
		//the child of the child process will calculate the first half
		if (id2 == 0)
		{
			sleep(1);
			//first close fd[0] that we don't need
			close(fd[0]);
			long	sum = 0;

			//add up first half
			for (int i = 0; i < count / 2; i++)
				sum = sum + arr[i];
			printf("The sum calculated from the child of child process(my id: %d, my parent's id: %d): %ld\n", getpid(), getppid(), sum);

			//write to fd[1]
			if (write(fd[1], &sum, sizeof(sum)) == -1)
			{
				printf("Error occured when writing!\n");
				free(arr);
				arr = NULL;
				free(fd);
				fd = NULL;
				exit(EXIT_FAILURE);
			}
			close(fd[1]);
			free(arr);
			arr = NULL;
			free(fd);
			fd = NULL;
			exit(EXIT_SUCCESS);
		}
		else
		{
			int	status;

			waitpid(id2, &status, 0);
			if (WIFEXITED(status))
			{
				if (WEXITSTATUS(status) == EXIT_SUCCESS)
				{
					long sum = 0;
					long sumC;
					long total;

					//add up the second half
					for (int i = count / 2; i < count; i++)
						sum = sum + arr[i];
					printf("The sum calculated from child process (my id: %d, my parent's id: %d): %ld\n", getpid(), getppid(), sum);

					//read from fd[0] to get child's child result
					if (read(fd[0], &sumC, sizeof(sumC)) == -1)
					{
						printf("Error occured when reading!\n");
						free(arr);
						arr = NULL;
						free(fd);
						fd = NULL;
						exit(EXIT_FAILURE);
					}

					total = sum + sumC;
					printf("The total sum is: %ld\n", total);
					
					//write to fd[1] the total
					if (write(fd[1], &total, sizeof(total)) == -1)
					{
						printf("Error occured when reading!\n");
						free(arr);
						arr = NULL;
						free(fd);
						fd = NULL;
						exit(EXIT_FAILURE);
					}

					//close everything for this process
					close(fd[0]);
					close(fd[1]);
					free(arr);
					arr = NULL;
					free(fd);
					fd = NULL;
					exit(EXIT_SUCCESS);
				}
			}
			else
			{
				free(arr);
				arr = NULL;
				free(fd);
				fd = NULL;
				exit(EXIT_FAILURE);
			}
		}
	}
	else
	{
		//wait for child and it's child to terminate
		int	status;
		waitpid(id, &status, 0);
		if (WIFEXITED(status))
		{
			if (WEXITSTATUS(status) == EXIT_SUCCESS)
			{
				long	num;
				//first close fd[1] that we don't need
				close(fd[1]);
				if (read(fd[0], &num, sizeof(num)) == -1)
				{
					printf("Error occured when reading!\n");
					free(fd);
					fd = NULL;
					exit(EXIT_FAILURE);
				}
				printf("Reading from the child process, the OG process (my id: %d, my parent's id: %d) get this number: %ld\n", getpid(), getppid(), num);
				close(fd[0]);
				free(fd);
				fd = NULL;
			}
			else
			{
				free(fd);
				fd = NULL;
				exit(EXIT_FAILURE);
			}
		}
	}
	return (0);
}
