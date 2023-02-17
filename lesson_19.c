#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

//here we create our function
void	handle_sigtstp(int sig)
{
	printf("Stop not allowed\n");
}

void	handle_sigcont(int sig)
{
	printf("Input number: ");
	fflush(stdout);
}

int	main(int argc, char **argv)
{
	// //we prevent ctrl+z to suspend our program
	struct sigaction sa;//sigaction a struct from the signal.h header file, why not typedef it
	sa.sa_handler = &handle_sigcont;//sa_handler is a pointer on function 
	sa.sa_flags = SA_RESTART;
	sigaction(SIGCONT, &sa, NULL);

	//signal(SIGTSTP, &handle_sigtstp);//does the same thing, but it's behavior varies across different versions of unix system (portability issue), hence sigaction is preferable

	int	x;
	printf("Input number: ");
	scanf("%d", &x);
	printf("Result %d * 5 = %d\n", x, x * 5);
	return (0); 
}
