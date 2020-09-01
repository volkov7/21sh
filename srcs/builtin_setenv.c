/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_setenv.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 16:07:21 by jsance            #+#    #+#             */
/*   Updated: 2020/08/07 13:25:46 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		set_new_var(t_envlist **tmp, char **new_var)
{
	if ((((*tmp)->next = create_env_node(*new_var)) == NULL))
	{
		ft_strdel(new_var);
		return (FUNC_ERROR);
	}
	ft_strdel(new_var);
	return (FUNC_SUCCESS);
}

int		set_env(t_envlist **envlst, char *var, char *value)
{
	t_envlist	*tmp;
	size_t		len;
	char		*new_var;

	tmp = *envlst;
	len = ft_strlen(var);
	if ((new_var = ft_join_str_str_str(var, "=", value)) == NULL)
		return (FUNC_ERROR);
	while (tmp != NULL)
	{
		if ((ft_strncmp(tmp->value, var, len) == 0) && tmp->value[len] == '=')
		{
			ft_strdel(&tmp->value);
			tmp->value = new_var;
			break ;
		}
		else if (tmp->next == NULL)
		{
			if (set_new_var(&tmp, &new_var) == FUNC_ERROR)
				return (FUNC_ERROR);
			break ;
		}
		tmp = tmp->next;
	}
	return (FUNC_SUCCESS);
}

void	setenv_error(char *err, int exit_status, t_proc *proc)
{
	write(2, err, ft_strlen(err));
	if (proc->pid == UNINIT)
		handle_exit_status(EXIT_FAILURE);
	else if (proc->pid == 0)
		exit(exit_status);
}

void	builtin_setenv(char **argv, t_envlist **envlst, t_proc *proc)
{
	if (argv[1] == NULL)
		setenv_error(E_TOO_FEW_ARGS, EXIT_FAILURE, proc);
	else if (argv[2] != NULL && argv[3] != NULL)
		setenv_error(E_TOO_MANY_ARGS, EXIT_FAILURE, proc);
	if (set_env(envlst, argv[1], (argv[2] == NULL) ? "\0" : argv[2]) == -1)
		setenv_error(E_ALLOC_MEMORY, EXIT_FAILURE, proc);
	if (proc->pid == UNINIT)
		handle_exit_status(EXIT_SUCCESS);
	else if (proc->pid == 0)
		exit(EXIT_SUCCESS);
}
