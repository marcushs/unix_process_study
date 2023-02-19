#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int	fd[2];
	if (pipe(fd) == -1)
		return (7);
	int	pid = fork();
	if (pid == -1)
		return (2);
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], STDOUT_FILENO);
		close(fd[1]);
		char *str[] = {"ping", "-c", "3", "google.com", NULL};
		execvp("ping", str);
		int err = errno;
		printf("Error occured with errno: %d\n", err);
	}
	int	pid2 = fork();
	if (pid2 == -1)
		return (7);
	if (pid2 == 0)
	{
		close(fd[1]);
		dup2(fd[0], STDIN_FILENO);
		close(fd[0]);
		char *str[] = {"grep", "rtt", NULL};
		execvp("grep", str);
		int err = errno;
		printf("Error occured with errno: %d\n", err);
	}
	close(fd[0]);//never forget to close all fds in parent process as well
	close(fd[1]);
	waitpid(pid, NULL, 0);
	waitpid(pid2, NULL, 0);
	return (0);
}
