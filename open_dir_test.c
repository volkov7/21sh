#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int		main(void)
{
	int		fd;
	char	*file = "./obj";

	fd = open(file, O_RDONLY | O_CREAT | O_NONBLOCK, 0644);
	if (fd == -1)
	{
		printf("Error %s\n", file);
		return (0);
	}
	else
		printf("It's opened\n");
	close(fd);
	return (0);
}