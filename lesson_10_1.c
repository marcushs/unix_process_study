#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

int	main(int argc, char **argv)
{
	int	arr[5];
	srand(time(NULL));//takes the return value of time as seed, than generate pseudo random numbers from that
	for (int i = 0; i < 5; i++)
	{
		arr[i] = rand() % 100;//rand returns a pseudo-random number in the range 0 to RAND_MAX
		printf("Generated %d\n", arr[i]);
	}

	int	fd = open("sum", O_WRONLY);
	if (fd == -1)//tips from codevault, always check for error and handle
		return (1);
	
	// for (int i = 0; i < 5; i++)
	// {
	// 	if (write(fd, &arr[i], sizeof(int)) == -1)
	// 		return (2);
	// 	printf("Wrote %d\n", arr[i]);
	// }
	if (write(fd, &arr, sizeof(int) * 5) == -1) //more optimized, one write() call rather than 5 
		return (2);
	printf("Wrote array\n");
	close(fd);
	int fd2 = open("sum", O_RDONLY);
	int sum;
	if (fd2 == -1)
		return (3);
	if (read(fd2, &sum, sizeof(int)) == -1)
		return (4);
	printf("Read sum from fifo: %d\n", sum);
	close(fd2);
	return (0);
}
