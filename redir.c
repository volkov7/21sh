#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <stdio.h>

#define TMP "file.txt"

int		main(void)
{
	pid_t		child 		= -1;
	char		*cmd		= NULL;
	char		*args[3];
	int			fd;

	cmd = "/bin/ls";
	args[0] = cmd;
	args[1] = "-lF";
	args[2] = NULL;

	fd = open(TMP, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("error");
		return (-1);
	}

	child = fork();
	switch ((int)child)
	{
		case -1:
			close(fd);
			perror("ERROR");
			break;
		case 0:
			dup2(fd, STDOUT_FILENO);
			execve(cmd, args, NULL);
			perror("ERROR");
			break ;
	}
	close(fd);
	wait(NULL);
	return (0);
}