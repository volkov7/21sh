#include "lexer.h"

static int	check_exit_status(char *status)
{
	size_t	len;
	size_t	i;

	len = ft_strlen(status);
	if (len > 19)
		return (FUNC_FAIL);
	else
	{
		i = 0;
		while (status[i] != '\0')
		{
			if (ft_isdigit(status[i]) == 0)
				return (FUNC_FAIL);
			i++;
		}
	}
	return (FUNC_SUCCESS);
}

void		builtin_exit(char **argv)
{
	write(2, "exit\n", 5);
	if (argv[1] != NULL && argv[2] == NULL)
	{
		if (check_exit_status(argv[1]) == FUNC_SUCCESS)
			exit(ft_atoi(argv[1]));
		write(2, "numeric argument required\n", 26);//need print wrong argument
		exit(255);
	}
	else if (argv[1] != NULL && argv[2] != NULL)
	{
		write(2, "exit: too many arguments\n", 25 );//need print wrong argument
		return ;
	}
	else
		exit(handle_exit_status(GET_EXIT_STATUS));
}
