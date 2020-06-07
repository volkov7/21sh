/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 14:01:08 by nriker            #+#    #+#             */
/*   Updated: 2020/03/08 14:29:15 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// void		quote(t_input *input)
// {
// 	if (!input->qoute)
// 	{

// 	}
// }

int			check_quotes(t_input *input)
{
	int		flag;
	char	q1;
	int		i;

	i = -1;
	flag = 1;
	if (!ft_strlen(input->line))
		return (0);
	while (input->line[++i])
		if (input->line[i] == '\'' || input->line[i] == '\"')
		{
			q1 = input->line[i];
			i++;
			while (input->line[i] != q1 && input->line[i])
				i++;
			if (!input->line[i])
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
				return (1);
			}
		}
	// if (input->flag)
	// {
	// 	input->qt = 0;
	// 	input->quote = 0;
	// 	input->dquote = 0;
	// }
	return (0);
}
