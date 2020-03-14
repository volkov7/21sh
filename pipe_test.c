#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>

void	run_pipe(void)
{
	int const	READ_END 	= 0;
	int const	WRITE_END	= 1;
	pid_t		child 		= -1;
	char		*cmd1		= NULL;
	char		*cmd2		= NULL;
	char		*cmd3		= NULL;
	char		*args1[3];
	char		*args2[3];
	char		*args3[3];
	char		**jobs[4];
	int			pdes[2];

	cmd1 = "/bin/ls";
	args1[0] = cmd1;
	args1[1] = "-1";
	args1[2] = NULL;

	cmd2 = "/bin/cat";
	args2[0] = cmd2;
	args2[1] = "-e";
	args2[2] = NULL;

	cmd3 = "usr/bin/grep";
	args3[0] = cmd3;
	args3[1] = "21";
	args3[2] = NULL;

	jobs[0] = args1;
	jobs[1] = args2;
	jobs[2] = args3;
	jobs[3] = NULL;

	pipe(pdes);

	child = fork();
	switch ((int)child)
	{
		case -1:
			close(pdes[READ_END]);
			close(pdes[WRITE_END]);
			perror("ERROR");
			break;
		case 0:
			dup2(pdes[WRITE_END], STDOUT_FILENO);
			close(pdes[READ_END]);
			execve(cmd1, args1, NULL);
			perror("ERROR");
			break ;
	}
	//parent
	dup2(pdes[READ_END], STDIN_FILENO);
	close(pdes[WRITE_END]);
	wait(NULL);
	execve(cmd2, args2, NULL);
}

int		main(void)
{
	pid_t	child = -1;

	child = fork();
	switch ((int)child)
	{
		case -1:
			perror("ERROR");
			break ;
		case 0:
			run_pipe();
			perror("ERROR");
			break ;
	}
	// parrent
	wait(NULL);
	return (0);
}