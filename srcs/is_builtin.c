#include "lexer.h"

int		find_builtin(char *command)
{
	if (ft_strequ(command, "exit") || ft_strequ(command, "cd")
	|| ft_strequ(command, "echo") || ft_strequ(command, "env")
	|| ft_strequ(command, "setenv") || ft_strequ(command, "unsetenv")
	|| ft_strequ(command, "type"))
		return (FUNC_SUCCESS);
	return (FUNC_FAIL);
}

int		is_builtin(char *command, t_proc **proc)
{
	if (find_builtin(command) == FUNC_SUCCESS)
	{
		(*proc)->is_builtin = 1;
		return (FUNC_SUCCESS);
	}
	return (FUNC_FAIL);
}
