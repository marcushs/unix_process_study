#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//This program is written to test ctrl+z and fg in the terminal

int	main(int argc, char **argv)
{
	int	x;
	printf("PID of this process: %d\n", getpid());
	printf("Input number: ");
	scanf("%d", &x);
	printf("Result %d * 5 = %d\n", x, x * 5);
	return (0);
}
