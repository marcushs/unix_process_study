#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h> //this header file allows us to know what goes wrong in a program
//#include <process.h>

/* exec family functions:
 for windows: include <process.h>, 
 for linux: include <unistd.h>
*/

/*execl:   finds the executable of the given path, then starts the process (l in execl stands for list of args)
  execlp:  use the PATH variable of the given executable name instead, no need to give the whole path manually, just the name (ping for example)
  execvp:  instead of a list of args that we code, we need to have a 'v'ector, meaning an array
  execvpe: adding 'e' letter for the exec family functions, 'e' stands for environment
*/
int	main(int argc, char **argv)
{
	//for execvp
	char* arr[] = {"ping", "google.com", NULL};
	//for execvpe
	char* env[] = {"TEST=environment variable", NULL};

	//execvp("push_swap", push);
	/*for execl, argvs are going after the path of the executable (whereis ping)
	First argument is always the path begin executed, in other words, a second time the path
	After that is the actual arguments for the "ping" program, e.g. google.com
	The last param is a null pointer
	*/

	// execl(
	// 	"/usr/bin/ping",
	// 	"/usr/bin/ping",
	// 	"google.com",
	// 	NULL);

	/*used argv[1] of lesson_1.c instead of hardcoding the address here*/
	//execlp("ping", "ping", argv[1], NULL);

	//execvp: first the target program, then the array of arguments (arr)
	//execvp("ping", arr);

	//test for err
	//execvp("pings", arr);

	/*execvpe: 'env' here is equivalent to the 'char *envp[]' in 
	int main(int argc, char **argv, char **envp)*/
	char *arr1[] = {"env", NULL};
	execvpe("env", arr1, env); //output: TEST=environment variable

	//for error management: errno, in our case we'll get 2, ENOENT, can't find "pings", see errno.h error codes
	int	err = errno;
	printf("Error occured: %d\n", err);
	
	printf("ping finished executing\n");
	return (0);
}
