#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	//creating a FIFO file, Create a new FIFO named PATH, with permission bits MODE (who can access what)
	if (mkfifo("myfifo1", 0777) == -1)
	{
		if (errno != EEXIST) //if it is not because a fifo file already exist in the directory and we still get -1, sth wrong
		{
			printf("Could not create fifo file\n");
			return (1);
		}
		// else
		// {
		// 	printf("FIFO file already exist!\n");
		// 	return (2);
		// }
		
		//before we can use our FIFO file like a pipe, we need to open it
		printf("Opening...\n");
		int fd = open("myfifo1", O_WRONLY);
		if (fd == -1)
			return (3);
		printf("Opened!\n");
		int	x = 97;
		if (write(fd, &x, sizeof(int)) == -1)
			return (2);
		printf("Written!\n");
		close(fd);
		printf("Closed!\n");
	}
	return (0);
}
