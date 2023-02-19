#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int	main(int argc, char **argv)
{
	int	fd[2];
	if (pipe(fd) == -1)
		return (1);
	int	pid = fork();
	if (pid == -1)
		return (2);
	if (pid == 0)
	{
		close(fd[0]);
		char str[200];
		int	len;
		printf("Input string here: ");
		fgets(str, 200, stdin);//better option than scanf, however the string we get is newline-terminated
		len = strlen(str);
		str[len - 1] = 0;
		if (write(fd[1], &len, sizeof(int)) == -1)
			return (3);
		printf("Wrote strlen %d to pipe\n", len);
		if (write(fd[1], str, len) == -1)
			return (4);
		printf("Wrote str to the pipe: %s\n", str);
		close(fd[1]);
	}
	else
	{
		close(fd[1]);
		int		wstatus;
		int		len;
		char	str[200];
		wait(&wstatus);
		if (WIFEXITED(wstatus))
		{
			if (WEXITSTATUS(wstatus) == 0)
			{
				if (read(fd[0], &len, sizeof(int)) == -1)
					return (5);
				printf("Received len %d from child process.\n", len);
				if (read(fd[0], str, len) == -1)
					return (6);
				printf("The string received from the child process is: %s\n", str);
			}
		}
		close(fd[0]);
	}
	return (0);
}
