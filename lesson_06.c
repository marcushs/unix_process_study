#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

int	main(int argc, char **argv)
{
	int	id1 = fork();
	int	id2 = fork();
	//printf("id1: %d id2: %d\n", id1, id2);
	if (id1 != 0)
	{
		if (id2 != 0)
			printf("I am the OG process: id1 == %d, id2 == %d\n", id1, id2);
		else
			printf("I am child of the OG process: id1 == %d, id2 == %d\n", id1, id2);
	}
	else
	{
		if (id2 != 0)
			printf("I am child of the OG process: id1 == %d, id2 == %d\n", id1, id2);
		else
			printf("I am child of child: id1 == %d, id2 == %d\n", id1, id2);
	}
	while (wait(NULL) != -1 || errno != ECHILD)
		printf("Waited for a child to finish\n");
	return (0);
}
