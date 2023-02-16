#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		int	file = open("pingResult.txt", O_WRONLY | O_CREAT, 0777);//create file with open()
		if (file == -1)
			return (3);

		printf("FD to pingResult.txt: %d\n", file);
		//int	file2 = dup(file);//dup() duplicates a file, returning a new fd pointing to the same file
		int	file2 = dup2(file, STDOUT_FILENO);//dup2() does the same thing, but we can assigne a fd value we want, it will close fd if already exist (STDOUT_FILENO is 1
		printf("The duplicated FD to pingResult.txt: %d\n", file2);//we will see this line in the file, not the stdout console

		close(file);//don't forget to close

		//so before we call exec(), before the process is being replaces by it, we call dup2() to replace stdout with our file, and its fd remains just like its process id
		int err = execlp("ping", "ping", "-c", "3", "google.com", NULL);
		if (err == -1)
		{
			printf("Command not found!\n");
			return (2);
		}
	}
	else
	{
		int	wstatus;
		wait(&wstatus);
		if (WIFEXITED(wstatus))
		{
			int	statusCode = WEXITSTATUS(wstatus);
			if (statusCode == 0)
				printf("Success!\n");
			else
				printf("Failure with exit code %d\n", statusCode);
		}
		printf("Some post processing goes here!\n");
	}
	return (0);
}
