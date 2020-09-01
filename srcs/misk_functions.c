/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misk_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 10:25:12 by jsance            #+#    #+#             */
/*   Updated: 2020/08/02 10:27:20 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ft_strarrdel(char ***arr)
{
	size_t	i;

	i = 0;
	if (arr != NULL && *arr != NULL)
	{
		while ((*arr)[i] != NULL)
		{
			ft_strdel(&(*arr)[i]);
			i++;
		}
		free(*arr);
		*arr = NULL;
	}
}

int		replace_value(char **str, char *value, size_t start, size_t len)
{
	char	*fresh;
	size_t	value_len;

	if (value != NULL)
		value_len = ft_strlen(value);
	else
		value_len = 0;
	if ((fresh = ft_strnew(ft_strlen(*str) - len + value_len)) == NULL)
	{
		handle_exit_status(EXIT_FAILURE);
		return (FUNC_ERROR);
	}
	ft_strncpy(fresh, *str, start);
	if (value != NULL)
		ft_strcat(fresh, value);
	ft_strcat(fresh, &(*str)[start + len]);
	ft_strdel(str);
	*str = fresh;
	return (FUNC_SUCCESS);
}

char	*ft_join_str_str_str(char *s1, char *s2, char *s3)
{
	char	*fresh;

	if (s1 == NULL || s2 == NULL || s3 == NULL)
		return (NULL);
	fresh = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3));
	if (fresh == NULL)
		return (NULL);
	ft_strcpy(fresh, s1);
	ft_strcat(fresh, s2);
	ft_strcat(fresh, s3);
	return (fresh);
}

int		validate_binary(char *binary)
{
	struct stat	st;

	if (access(binary, F_OK) == -1)
		return (shell_err(E_NO_EXIST, binary, EXIT_NOT_FOUND));
	if (access(binary, X_OK) == -1)
		return (shell_err(E_NO_PERM, binary, EXIT_NOT_EXECUTE));
	if (stat(binary, &st) == -1)
		return (shell_err(E_CANT_GET_STAT, binary, EXIT_NOT_EXECUTE));
	if (S_ISDIR(st.st_mode))
		return (shell_err(E_IS_DIR, binary, EXIT_NOT_EXECUTE));
	return (FUNC_SUCCESS);
}

void	clean_after_fork(t_proc *proc, int fds[3], int pipes[2])
{
	if (fds[0] != STDIN_FILENO && fds[0] != UNINIT)
		close(fds[0]);
	if (fds[1] != STDOUT_FILENO && fds[1] != UNINIT)
		close(fds[1]);
	fds[0] = pipes[0];
	if (proc->binary != NULL)
		ft_strdel(&proc->binary);
	if (proc->argv != NULL)
		ft_strarrdel(&proc->argv);
	if (proc->env != NULL)
		ft_strarrdel(&proc->env);
}
