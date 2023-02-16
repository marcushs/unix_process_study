#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>

int	main(int argc, char **argv)
{
	//generate a number, send to another process, it will then be multiplied and send back to the original process
	int p1[2];//child to parent
	int p2[2];//parent to child

	if (pipe(p1) == -1)
		return (1);
	if (pipe(p2) == -1)
		return (1);
	int	pid = fork();
	if (pid == -1)
		return (2);
	if (pid == 0)
	{
		//child process
		close(p1[0]);//as we do not need the read end of this pipe, we close straight away
		close(p2[1]);//as we do not need the write end of this pipe, we close straight away
		int	x;
		if (read(p2[0], &x, sizeof(int)) == -1)
			return (3);
		printf("Child received from pipe %d\n", x);
		x *= 4;
		printf("Multiplied by 4: %d\n", x);
		if (write(p1[1], &x, sizeof(int)) == -1)
			return (4);
		printf("Child wrote to pipe %d\n", x);
		close(p2[0]);
		close(p1[1]);
	}
	else
	{
		//parent process
		close(p1[1]);//we dont need to write on this pipe
		close(p2[0]);//same logic
		srand(time(NULL));
		int	y = rand() % 10;
		if (write(p2[1], &y, sizeof(int)) == -1)
			return (5);
		//printf("Parent wrote to pipe %d\n", y);
		if (read(p1[0], &y, sizeof(int)) == -1)
			return (6);
		printf("The result is %d\n", y);
		close(p2[1]);
		close(p1[0]);
		wait(NULL);//if we did not wait() here, the program will terminate anyway, child process might not execute
	}
	return (0);
}
