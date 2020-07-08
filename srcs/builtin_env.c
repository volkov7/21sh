/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 14:58:49 by jsance            #+#    #+#             */
/*   Updated: 2020/07/06 14:58:50 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	env_error(char *error, char c)
{
	write(2, "env: ", 5);
	write(2, error, ft_strlen(error));
	if (c != '\0')
		write(2, &c, 1);
	write(2, "\n", 1);
	exit(EXIT_FAILURE);
}

void	env_set_options(char **argv, size_t *i, int *opt)
{
	size_t	j;

	while (argv[*i] != NULL && argv[*i][0] == '-')
	{
		if (argv[*i][1] == 'i')
		{
			j = 0;
			while (argv[*i][++j] == 'i')
				(*opt) |= ENV_OPT_I;
			if (argv[*i][j] != '\0')
				env_error(E_ILLEGAL_OPT, argv[*i][j]);
		}
		else
			env_error(E_ILLEGAL_OPT, argv[*i][1]);
		(*i)++;
	}
}

void	print_env(t_proc *proc)
{
	size_t	i;

	i = 0;
	while (proc->env[i] != NULL)
	{
		ft_putendl(proc->env[i]);
		i++;
	}
}

void	builtin_env(t_proc *proc, t_envlist *envlst)
{
	size_t	i;
	int		opt;

	i = 1;
	env_set_options(proc->argv, &i, &opt);
	if (proc->argv[i] == NULL)
	{
		print_env(proc);
		exit(EXIT_SUCCESS);
	}
	if (find_builtin(proc->argv[i]) == FUNC_SUCCESS)
		env_error(E_IT_BUILTIN, '\0');
	else
	{
		check_binary(proc->argv[i], &proc->binary, envlst);
		if (proc->binary != NULL)
			execve(proc->binary, proc->argv + i,
									(opt & ENV_OPT_I) ? NULL : proc->env);
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}
