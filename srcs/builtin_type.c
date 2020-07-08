/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_type.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 16:03:27 by jsance            #+#    #+#             */
/*   Updated: 2020/07/06 16:07:10 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static void	type_print(char *command, char *binary)
{
	ft_putstr(command);
	ft_putstr(" is ");
	ft_putendl(binary);
}

static int	type_is_binary(char *command, t_envlist *envlst)
{
	char	*binary;

	binary = NULL;
	if (find_binary(command, &binary, envlst) == FUNC_SUCCESS && binary != NULL)
	{
		type_print(command, binary);
		ft_strdel(&binary);
		return (FUNC_SUCCESS);
	}
	return (FUNC_FAIL);
}

static int	type_is_executable(char *command)
{
	char	*cwd;
	char	*newpath;

	if (ft_strchr(command, '/') == NULL)
		return (FUNC_FAIL);
	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		ft_putstr_fd("type: ", 2);
		ft_putstr_fd(E_CANT_GET_CWD, 2);
		return (FUNC_FAIL);
	}
	if ((newpath = canonical_form(cwd, command)) == NULL)
		return (FUNC_FAIL);
	ft_strdel(&cwd);
	if (access(newpath, F_OK) == -1 || access(newpath, X_OK) == -1)
		return (FUNC_FAIL);
	type_print(command, command);
	ft_strdel(&newpath);
	return (FUNC_SUCCESS);
}

static int	type_is_builtin(char *command)
{
	if (find_builtin(command) == FUNC_SUCCESS)
	{
		ft_putstr(command);
		ft_putstr(" is a shell builtin\n");
		return (FUNC_SUCCESS);
	}
	return (FUNC_FAIL);
}

void		builtin_type(char **argv, t_envlist *envlst)
{
	size_t	i;

	i = 1;
	handle_exit_status(EXIT_SUCCESS);
	while (argv[i] != NULL)
	{
		if (type_is_builtin(argv[i]) == FUNC_FAIL
		&& type_is_binary(argv[i], envlst) == FUNC_FAIL
		&& type_is_executable(argv[i]) == FUNC_FAIL)
		{
			handle_exit_status(EXIT_FAILURE);
			ft_putstr_fd(argv[i], 2);
			ft_putstr_fd(" not found\n", 2);
		}
		i++;
	}
	exit(handle_exit_status(GET_EXIT_STATUS));
}
