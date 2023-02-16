#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int	main(int argc, char *argv[])
{
	int id = fork();
	//first fork here, now we have 2 processes
	//id = fork();
	//on this line, each of those 2 processes call fork(), hence 4 processes now
	//id = fork();
	//and so on ...
	if (id != 0)
		id = fork();
	//in this case, we only get 3 processes in the end, only one main
	printf("Process id: %d Hello world!\n", id);
}
