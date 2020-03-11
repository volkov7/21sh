#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>

int		main(void)
{
	pid_t		child 		= -1;
	pid_t		pid 		= -1;
	char		*cmd1		= NULL;
	char		*args1[4];
	int			status;
	int			opt;

	cmd1 = "/bin/ls";
	args1[0] = cmd1;
	args1[1] = "-1";
	args1[2] = "word";
	args1[3] = NULL;

	child = fork();
	switch ((int)child)
	{
		case -1:
			perror("ERROR");
			break;
		case 0:
			execve(cmd1, args1, NULL);
			perror("ERROR");
			break ;
	}
	//parent
	// wait(&status);
	opt = WUNTRACED | WNOHANG | WCONTINUED;
	printf("child = %d\n", child);
	for (int i = 0; i < 15; i++)
	{
		pid = waitpid(-1, &status, opt);
		if (pid == -1)
		{
			perror("Error");
			break ;
		}
		else if (pid == 0)
		{
			printf("Parrent still waiting...\n");
			sleep(1);
		}
		else if (pid == child)
			printf("child ended\n");
	}
	printf("pid = %d\n", pid);
	printf("Exit status = %d\n", status);
	printf("WEXITSTATUS = %d\n", WEXITSTATUS(status));
	return (0);
}