/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_routine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 15:09:00 by jsance            #+#    #+#             */
/*   Updated: 2020/07/06 15:09:01 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		check_if_number(char *word_fd)
{
	size_t	i;

	i = 0;
	while (word_fd[i] != '\0')
	{
		if (ft_isdigit(word_fd[i]) == 0)
			return (FUNC_FAIL);
		i++;
	}
	return (FUNC_SUCCESS);
}

int		close_fd(int fd)
{
	if (close(fd) == -1)
		return (FUNC_ERROR);
	return (FUNC_SUCCESS);
}

int		set_fd(int *fd, char *word_fd)
{
	struct stat	st;

	if (check_if_number(word_fd) == FUNC_FAIL)
		return (shell_err(E_FILEN_NUMBER, NULL, EXIT_FAILURE));
	*fd = ft_atoi(word_fd);
	if (fstat(*fd, &st) == -1)
		return (shell_err(E_BAD_FD, word_fd, EXIT_FAILURE));
	return (FUNC_SUCCESS);
}

void	initial_set_fd(t_ast *redir, char **file, int *stream_fd, int flag)
{
	if (redir->right->type == IO_NUMBER)
	{
		*file = redir->right->left->str;
		*stream_fd = ft_atoi((const char *)redir->right->str);
	}
	else
	{
		*file = redir->right->str;
		*stream_fd = (flag ? STDOUT_FILENO : STDIN_FILENO);
	}
}
