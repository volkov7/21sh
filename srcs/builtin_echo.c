/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 15:07:54 by jsance            #+#    #+#             */
/*   Updated: 2020/07/06 15:08:37 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	echo_special_character(char c)
{
	if (c == 'a')
		return ('\a');
	else if (c == 'b')
		return ('\b');
	else if (c == 'c')
		return ('c');
	else if (c == 'f')
		return ('\f');
	else if (c == 'n')
		return ('\n');
	else if (c == 'r')
		return ('\r');
	else if (c == 't')
		return ('\t');
	else if (c == 'v')
		return ('\v');
	else if (c == '\\')
		return ('\\');
	else
		return (0);
}

static void	echo_replace_special_char(char **str, int *c)
{
	size_t	i;
	size_t	rep;
	char	spec_char;

	i = 0;
	rep = 0;
	while ((*str)[i] != '\0')
	{
		spec_char = echo_special_character((*str)[i + 1]);
		if ((*str)[i] == '\\' && spec_char != 0)
		{
			if (spec_char == 'c')
			{
				*c = 0;
				break ;
			}
			i++;
			(*str)[rep] = spec_char;
		}
		else
			(*str)[rep] = (*str)[i];
		i++;
		rep++;
	}
	ft_bzero(&(*str)[rep], i - rep);
}

int			str_is_opt_echo(char *opt)
{
	size_t	i;

	i = 0;
	while (opt[++i] != '\0')
	{
		if (opt[i] != 'n' && opt[i] != 'e' && opt[i] != 'E')
			return (FUNC_FAIL);
	}
	return (FUNC_SUCCESS);
}

static void	echo_set_options(char **argv, int *opt, size_t *i)
{
	size_t	j;

	while (argv[*i] != NULL)
	{
		if (argv[*i][0] == '-' && (str_is_opt_echo(argv[*i]) == FUNC_SUCCESS))
		{
			j = 0;
			while (argv[*i][++j] != '\0')
			{
				if (argv[*i][j] == 'n')
					*opt |= ECHO_OPT_SMALL_N;
				else if (argv[*i][j] == 'e')
					*opt |= ECHO_OPT_SMALL_E;
				else if (argv[*i][j] == 'E')
					*opt |= ECHO_OPT_E;
			}
		}
		else
			return ;
		(*i)++;
	}
}

void		builtin_echo(char **argv)
{
	size_t	i;
	int		opt;
	int		c;

	opt = 0;
	i = 1;
	c = 1;
	echo_set_options(argv, &opt, &i);
	while (argv[i] != NULL && c)
	{
		if ((opt & ECHO_OPT_E) == 0
			|| (((opt & ECHO_OPT_E) && ((opt & ECHO_OPT_SMALL_E)))))
			echo_replace_special_char(&argv[i], &c);
		ft_putstr(argv[i]);
		if (argv[i + 1] != NULL && c == 1)
			ft_putchar(' ');
		i++;
	}
	if ((opt & ECHO_OPT_SMALL_N) == 0 && c == 1)
		ft_putchar('\n');
	exit(EXIT_SUCCESS);
}
