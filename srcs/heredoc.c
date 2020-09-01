/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 10:41:12 by jsance            #+#    #+#             */
/*   Updated: 2020/08/07 13:08:06 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int				is_valid_delim(t_tokenlst *token)
{
	if (token->type != WORD)
		return (shell_err(E_PARSE_NEAR, get_token_str(token->type), 1));
	if (is_contain_quote(token->str) == FUNC_SUCCESS)
	{
		quote_removal(&(token->str), 0);
		token->flags |= HEREDOC_NOEXP;
	}
	handle_exit_status(EXIT_SUCCESS);
	return (FUNC_SUCCESS);
}

char			*parrent_fork(int pipes[2])
{
	char		buf;
	int			status;
	char		*line;

	status = 0;
	line = NULL;
	close(pipes[1]);
	wait(&status);
	if (WIFEXITED(status) != 0)
	{
		if (WEXITSTATUS(status) == SIGINT)
		{
			handle_exit_status(128 + SIGINT);
			return (NULL);
		}
		if (WEXITSTATUS(status) == EXIT_FAILURE)
			handle_exit_status(CTRLD);
	}
	while (read(pipes[0], &buf, 1) > 0)
		ft_realloc(&line, &buf);
	ft_realloc(&line, "\n");
	close(pipes[0]);
	return (line);
}

char			*fork_heredoc_inp(t_init *in, t_input *input)
{
	int			pipes[2];
	pid_t		pid;
	char		*line;

	line = NULL;
	if (pipe(pipes) == -1)
		return (shell_char_err(E_CANT_CREAT_PIPE, NULL, EXIT_FAILURE));
	pid = fork();
	if (pid == -1)
		shell_exit_err(E_FORK_FAIL, NULL, EXIT_FAILURE);
	if (pid == 0)
	{
		signal(SIGINT, (void*)child_need_to_die);
		close(pipes[0]);
		read_input_heredoc(in, input, 2, pipes[1]);
	}
	else
		line = parrent_fork(pipes);
	ft_putchar('\n');
	return (line);
}

int				handle_input_heredoc(t_init *in, t_input *input,
									t_tokenlst *token, char *delim)
{
	char		*line;
	char		*res_line;

	res_line = NULL;
	ft_strdel(&(token->str));
	while (1)
	{
		line = fork_heredoc_inp(in, input);
		if (line == NULL || ft_strequ(line, delim)
			|| handle_exit_status(GET_EXIT_STATUS) == CTRLD)
			break ;
		res_line = ft_strjoinfree(res_line, line);
		if (input->ctrl_d_line)
			free(input->ctrl_d_line);
		input->ctrl_d_line = ft_strdup(res_line);
		ft_strdel(&line);
		if (res_line == NULL)
			return (shell_err(E_ALLOC_MEMORY, NULL, EXIT_FAILURE));
	}
	if (line == NULL)
		ft_strdel(&res_line);
	if (set_input_heredoc(token, &res_line) == FUNC_ERROR)
		return (FUNC_ERROR);
	ft_strdel(&line);
	return (FUNC_SUCCESS);
}

int				here_doc(t_tokenlst **tokenlst, t_init *in, t_input *input)
{
	t_tokenlst	*tmp;
	char		*delim;

	tmp = *tokenlst;
	signal(SIGINT, SIG_IGN);
	while (tmp != NULL)
	{
		if (tmp->type == DLESS)
		{
			tmp = tmp->next;
			if (is_valid_delim(tmp) == FUNC_ERROR)
				return (FUNC_ERROR);
			if ((delim = ft_strjoin(tmp->str, "\n")) == NULL)
				return (shell_err(E_ALLOC_MEMORY, NULL, EXIT_FAILURE));
			if (handle_input_heredoc(in, input, tmp, delim) == FUNC_ERROR)
				return (FUNC_ERROR);
			ft_strdel(&delim);
		}
		tmp = tmp->next;
	}
	return (FUNC_SUCCESS);
}
