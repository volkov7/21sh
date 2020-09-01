/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 06:41:21 by nriker            #+#    #+#             */
/*   Updated: 2020/08/05 20:18:00 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		check_quotes_check(t_input *input, char q1)
{
	if (q1 == '\'')
	{
		input->qt = 1;
		input->quote = 1;
		input->dquote = 0;
	}
	else
	{
		input->qt = 1;
		input->dquote = 1;
		input->quote = 0;
	}
}

void		check_quotes_2(t_input *input, int *i, char *q1)
{
	(*q1) = input->line[(*i)];
	(*i)++;
	while (input->line[(*i)] != (*q1) && input->line[(*i)])
		(*i)++;
}

int			check_quotes(t_input *input)
{
	char	q1;
	int		i;

	i = -1;
	if (!ft_strlen(input->line))
		return (0);
	if (!input->heredok)
	{
		while (input->line[++i])
		{
			if (input->line[i] == '\'' || input->line[i] == '\"')
			{
				check_quotes_2(input, &i, &q1);
				if (!input->line[i])
				{
					check_quotes_check(input, q1);
					return (1);
				}
			}
		}
	}
	return (0);
}
