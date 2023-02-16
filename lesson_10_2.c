#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int	arr[5];

	int fd = open("sum", O_RDONLY);
	if (fd == -1)
		return (1);
	for (int i = 0; i < 5; i++)
	{
		if (read(fd, &arr[i], sizeof(int)) == -1)
			return (2);
		printf("Received %d\n", arr[i]);
	}
	close(fd);
	int sum = 0;
	for (int i = 0; i < 5; i++)
		sum += arr[i];
	int fd2 = open("sum", O_WRONLY);
	if (fd2 == -1)
		return (4);
	if (write(fd2, &sum, sizeof(int)) == -1)
		return (3);
	printf("Wrote sum to fifo: %d\n", sum);
	close(fd2);
	return (0);
}
