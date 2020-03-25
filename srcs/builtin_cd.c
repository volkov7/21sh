#include "lexer.h"

void	cd_handle_exit(t_proc *proc, int exit_status)
{
	if (proc->pid == UNINIT)
		handle_exit_status(exit_status);
	else if (proc->pid == 0)
		exit(exit_status);
}

void	check_var(char *argpath, int opt, t_envlist **envlst, t_proc *proc)
{
	if (argpath == NULL || *argpath == '\0')
		cd_handle_exit(proc, EXIT_FAILURE);
	if (change_dir(argpath, opt, envlst) == FUNC_ERROR)
		cd_handle_exit(proc, EXIT_FAILURE);
}

int		str_is_option_cd(char *str)
{
	size_t	i;

	i = 0;
	while (str[++i] != '\0')
	{
		if (str[i] != 'P' && str[i] != 'L')
			return (FUNC_FAIL);
	}
	return (FUNC_SUCCESS);
}

void	cd_set_option(char **argv, size_t *i, int *opt)
{
	size_t	j;

	while (argv[*i] != NULL)
	{
		if (argv[*i][0] == '-' && argv[*i][1] != '\0'
		&& str_is_option_cd(argv[*i]) == FUNC_SUCCESS)
		{
			j = 0;
			while (argv[*i][++j])
			{
				if (argv[*i][j] == 'P')
					*opt = CD_OPT_P;
				else if (argv[*i][j] == 'L')
					*opt = CD_OPT_L;
			}
		}
		else
			return ;
		(*i)++;
	}
}

void	builtin_cd(char **argv, t_envlist **envlst, t_proc *proc)
{
	int		opt;
	size_t	i;

	i = 1;
	opt = CD_OPT_L;
	cd_set_option(argv, &i, &opt);
	handle_exit_status(EXIT_SUCCESS);
	if (argv[i] != NULL && argv[i + 1] != NULL && argv[i + 2] != NULL)
	{
		print_err(E_CD_MANY_ARG, NULL);
		cd_handle_exit(proc, EXIT_FAILURE);
	}
	else if (argv[i] != NULL && argv[i + 1] != NULL)
		chk_two_arguments(argv + i, proc, envlst, opt);
	else if (argv[i] != NULL && ft_strequ(argv[i], "-") == 1)
	{
		opt |= CD_OPT_PRINT;
		check_var(get_env_value("OLDPWD", *envlst), opt, envlst, proc);
	}
	else if (argv[i] == NULL || ft_strequ(argv[i], "--") == 1)
		check_var(get_env_value("HOME", *envlst), opt, envlst, proc);
	else
		change_dir(argv[i], opt, envlst);
}
