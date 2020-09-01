/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_misk.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 11:58:45 by jsance            #+#    #+#             */
/*   Updated: 2020/08/05 20:34:50 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int				is_contain_quote(char *str)
{
	size_t		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"' || str[i] == '\\')
			return (FUNC_SUCCESS);
		i++;
	}
	return (FUNC_FAIL);
}

int				str_check_spec(char *str)
{
	size_t		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (is_spec(str[i]))
			return (FUNC_SUCCESS);
		i++;
	}
	return (FUNC_FAIL);
}

int				set_input_heredoc(t_tokenlst *token, char **res_line)
{
	if (*res_line == NULL)
		token->str = ft_strnew(0);
	else
		token->str = *res_line;
	if (token->str == NULL)
		return (shell_err(E_ALLOC_MEMORY, NULL, EXIT_FAILURE));
	if (str_check_spec(token->str) == FUNC_SUCCESS)
		token->flags |= HAS_SPECIAL;
	token->flags |= IS_HEREDOC;
	return (FUNC_SUCCESS);
}

void			child_need_to_die(void)
{
	signal(SIGINT, (void*)child_need_to_die);
	get_curs_pos_inend(get_input(0));
	exit(SIGINT);
}

void			ft_realloc(char **line, const char *buf)
{
	char	*fresh;

	fresh = NULL;
	if (*line == NULL)
	{
		*line = ft_strnew(1);
		ft_strncat(*line, buf, 1);
	}
	else
	{
		fresh = ft_strnew(ft_strlen(*line) + 1);
		ft_strcat(fresh, *line);
		ft_strncat(fresh, buf, 1);
		free(*line);
		*line = fresh;
	}
}
