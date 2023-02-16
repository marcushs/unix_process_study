#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int	main(int argc, char **argv)
{
	//every single process has a unique id
	int	id = fork();
	if (id == 0)
		sleep(1);//sleep (wait) for 1 second, since the parent process will already be finished, a new parent will be assigned to the child process
	printf("Current ID: %d, parent ID: %d\n", getpid(), getppid()); //getppid() Get the process ID of the calling process's parent.
		//we notice that the parent process has also a parent process
	// if (id == 0)
	// 	printf("This is the child process: %d\n",getpid()); //getpid() Get the process ID of the calling process
	// else
	// 	printf("This is the parent process: %d\n",getpid()); 
	// if (id != 0)//not necessary, code still works without 
	// 	wait(NULL);
	int	res = wait(NULL);
	if (res == -1)
		printf("No children to wait for\n");
	else
		printf("%d finished execution\n", res);//id of child process get printed 
	return (0);
}
