# include <unistd.h>
# include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
int main ()
{
pid_t pid;
pid=fork();
if (pid < 0)
	printf("error in fork!\n");
else if (pid == 0)
	printf("i am the child process, my process id is %d\n",getpid());
else
	printf("i am the parent process, my process id is %d\n",getpid());
return 1;
}
