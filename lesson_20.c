#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

int	x = 0;//we make x a global variable so that we know that we have not answer that question after 5 sec

void	handle_signal(int sig)
{
	if (x == 0)
		printf("\n(HINT) Remeber that multiplication is repetitive addition!\n");
}

int	main(int argc, char **argv)
{
	int	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		//Child process
		sleep(5);
		kill(getppid(), SIGUSR1);
	}
	else
	{
		//Parent process
		struct sigaction sa = { 0 };
		sa.sa_flags = SA_RESTART;
		sa.sa_handler = &handle_signal;
		sigaction(SIGUSR1, &sa, NULL);

		printf("What is the result of 3 x 5 ? ");
		scanf("%d", &x);
		kill(pid, SIGTERM);
		if (x == 15)
			printf("Right!\n");
		else
			printf("Wrong!\n");
		wait(NULL);
	}
	return (0);
}
