#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>

int	main(int argc, char *argv[])
{
	int	id = fork();
	int	n;
	if (id == 0)
		n = 1;
	else
		n = 6;
	// in the main process, we wait
	if (id != 0)
		wait();
	for (int i = n; i < n + 5; i++)
	{
		printf("%d ", i);
		//fflush(), we need to flush the buffer for printf, because we would like stdout to print each number exactly when we call printf, instead of waiting for everything in the buffer the print all at the same time
		fflush(stdout);
	}
	//only print a line break when in main process, so at the end of our program
	if (id != 0)
		printf("\n");
	return (0);
}
