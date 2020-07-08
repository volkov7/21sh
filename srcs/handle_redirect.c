/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 15:10:07 by jsance            #+#    #+#             */
/*   Updated: 2020/07/06 15:10:08 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		create_heredoc_fd(char *str)
{
	int		pipes[2];

	handle_exit_status(EXIT_FAILURE);
	if (pipe(pipes) == -1)
		return (shell_err(E_CANT_CREAT_PIPE, NULL, EXIT_FAILURE));
	if (write(pipes[1], str, ft_strlen(str)) == -1)
	{
		close(pipes[0]);
		close(pipes[1]);
		return (FUNC_ERROR);
	}
	close(pipes[1]);
	handle_exit_status(EXIT_SUCCESS);
	return (pipes[0]);
}

int		redirect_input(t_ast *redir)
{
	char	*file;
	int		stream_fd;
	int		fd;

	initial_set_fd(redir, &file, &stream_fd, 0);
	if (redir->type == LESS)
		fd = open(file, O_RDONLY);
	else if (redir->type == DLESS)
		fd = create_heredoc_fd(file);
	else if (ft_strcmp(file, "-") == 0)
		return (close_fd(stream_fd));
	else if (set_fd(&fd, file) == FUNC_ERROR)
		return (FUNC_ERROR);
	if (fd == -1)
		return (shell_err(E_NO_EXIST, file, EXIT_FAILURE));
	if (dup2(fd, stream_fd) == -1)
		return (shell_err(E_DUP_FAIL, NULL, EXIT_FAILURE));
	if (redir->type == LESS || redir->type == DLESS)
		close(fd);
	return (FUNC_SUCCESS);
}

int		redirect_output(t_ast *redir)
{
	char	*file;
	int		stream_fd;
	int		fd;

	initial_set_fd(redir, &file, &stream_fd, 1);
	if (redir->type == GREAT)
		fd = open(file, GREAT_OPEN_FLAGS, PERMISSIONS);
	else if (redir->type == DGREAT)
		fd = open(file, DGREAT_OPEN_FLAGS, PERMISSIONS);
	else if (ft_strcmp(file, "-") == 0)
		return (close_fd(stream_fd));
	else if (set_fd(&fd, file) == FUNC_ERROR)
		return (FUNC_ERROR);
	if (fd == -1)
		return (shell_err(E_NO_EXIST, file, EXIT_FAILURE));
	if (dup2(fd, stream_fd) == -1)
		return (shell_err(E_DUP_FAIL, NULL, EXIT_FAILURE));
	if (redir->type == GREAT || redir->type == DGREAT)
		close(fd);
	return (FUNC_SUCCESS);
}

int		redirect(t_ast *node)
{
	if (node == NULL)
		return (FUNC_FAIL);
	if (node->type == GREAT || node->type == DGREAT || node->type == GREATAND)
		return (redirect_output(node));
	if (node->type == LESS || node->type == DLESS || node->type == LESSAND)
		return (redirect_input(node));
	return (FUNC_SUCCESS);
}

int		handle_redirs(t_ast *redir)
{
	if (redir == NULL)
		return (FUNC_FAIL);
	if (is_redirect(redir->type))
	{
		if (redirect(redir) == FUNC_ERROR)
			return (FUNC_ERROR);
	}
	if (handle_redirs(redir->left) == FUNC_ERROR)
		return (FUNC_ERROR);
	return (FUNC_SUCCESS);
}
