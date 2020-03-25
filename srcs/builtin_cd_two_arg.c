#include "lexer.h"

int		path_replace(char **argv, char *cwd, char **fresh)
{
	char	*search;
	size_t	rep_len;
	size_t	search_len;
	size_t	j;

	if (*cwd == '\0' || (search = ft_strstr(cwd, argv[0])) == NULL)
		return (FUNC_FAIL);
	rep_len = ft_strlen(argv[1]);
	search_len = ft_strlen(argv[0]);
	if (((*fresh) = ft_strnew(ft_strlen(cwd) - search_len + rep_len)) == NULL)
		return (FUNC_ERROR);
	j = 0;
	while (*cwd != '\0')
	{
		if (cwd == search)
		{
			ft_strcpy(&((*fresh)[j]), argv[1]);
			j += rep_len;
			cwd += search_len;
		}
		else
			(*fresh)[j++] = *cwd++;
	}
	(*fresh)[j] = '\0';
	return (FUNC_SUCCESS);
}

void	chk_two_arguments(char **argv, t_proc *proc, t_envlist **envlst,
																int opt)
{
	char	*cwd;
	char	*changed_cwd;
	int		ret;

	changed_cwd = NULL;
	cwd = get_env_value("PWD", *envlst);
	if (cwd == NULL || *cwd == '\0')
	{
		cd_error(NULL, NULL, NULL, NULL);
		cd_handle_exit(proc, EXIT_FAILURE);
	}
	ret = path_replace(argv, cwd, &changed_cwd);
	if (ret == FUNC_FAIL)
	{
		print_err(E_CD_NOT_IN_PWD, argv[0]);
		cd_handle_exit(proc, EXIT_FAILURE);
	}
	opt |= CD_OPT_PRINT;
	ret = change_dir(changed_cwd, opt, envlst);
	if (ret == FUNC_ERROR)
		cd_handle_exit(proc, EXIT_FAILURE);
	ft_strdel(&changed_cwd);
}
