#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
# include <sys/stat.h>

# define FILE	"./grammar"

int		main(void)
{
	int			fd;
	int			fd2;
	struct stat st;


	fd = open(FILE, O_RDONLY);
	fd2 = 3;
	if (fstat(fd2, &st) == -1)
		perror("fd");
	else
		printf("It's can get stat\n");
	return (0);
}