#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

/* same code as lesson 3, refer to video to see visualization of fork() function
main take away is that keep track of process id, and when fork() is called
we have two copies of the same process in 2 separate memory space*/
int	main (int argc, char **argv)
{
	int	id = fork();
	int	n;
	if (id == 0)
		n = 1;
	else
		n = 6;
	if (id != 0)
		wait();
	for (int i = n; i < n + 5; i++)
	{
		printf("%d ", i);
		fflush(stdout);
	}
	if (id != 0)
		printf("\n");
}
