#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

int	main(int argc, char **argv)
{
	int	pid = fork();

	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		/*Next 3 printf were used to clarify the pids of each process*/
		// printf("pid id child process: %d\n", pid);
		// printf("call getpid id child process: %d\n", getpid());
		// printf("parent id in child process: %d\n", getppid());

		while (1)
		{
			printf("Some output\n");
			usleep(50000);
		}
	}
	else
	{
		/*The next 2 printf were used to clarify pids of processes*/
		// printf("pid in parent process: %d\n", pid);
		// printf("call getpid in parent process: %d\n", getpid());

		//our parent process controls whether or not our child process executes it's code

		kill(pid, SIGSTOP);//we prevent the child process from running while we promtp the user

		int	t;
		do
		{
			printf("Time in seconds for execution: \n");
			scanf("%d", &t);

			if (t > 0)
			{
				kill(pid, SIGCONT);
				sleep(t);//as sleep takes in an unsigned int as param, if we pass in -1, we will wait for MAX_INT sec
				kill(pid, SIGSTOP);
			}
		} while (t > 0);//so after each run, we will get prompt again, input n <= 0 to quit the program
		

		/*below is a simple demo of sigcont and sigstop*/
		// kill(pid, SIGSTOP);//stop the child process
		// sleep(1);//wait for 1 sec, nothing happens
		// kill(pid, SIGCONT);//continue the child process
		// sleep(1);//for 1 sec, the child process execute, we see about 20 lines on stdout
		// kill(pid, SIGKILL);//terminate the child process before wait, so wait actually gets a terminated child process
		// wait(NULL);
	}
	return (0);
}
