#include "lexer.h"

void	print_err(char *err, char *arg)
{
	write(2, err, ft_strlen(err));
	if (arg != NULL)
		write(2, arg, ft_strlen(arg));
	write(2, "\n", 1);
}

int		cd_error(char *usedpath, char *argpath, char **newpath, char **cwd)
{
	if (usedpath == NULL)
		print_err(E_CD_CANT_GET_CWD, NULL);
	else if (access(usedpath, F_OK) == -1)
		print_err(E_CD_NO_EXIST, argpath);
	else if (access(usedpath, R_OK) == -1)
		print_err(E_CD_NO_PERM, argpath);
	else
		print_err(E_CD_NOT_A_DIR, argpath);
	ft_strdel(newpath);
	ft_strdel(cwd);
	handle_exit_status(EXIT_FAILURE);
	return (FUNC_ERROR);
}
