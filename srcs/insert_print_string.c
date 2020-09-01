/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_print_string.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 20:45:31 by nriker            #+#    #+#             */
/*   Updated: 2020/08/01 20:49:21 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		print_letter_q(t_input *input, char buf[7])
{
	ft_putchar(buf[0]);
	if (input->quote)
	{
		if (!(input->x_quote % input->col))
		{
			ft_putchar('\n');
			input->lines_in_com++;
			input->qlines_in_com++;
		}
	}
	else if (input->dquote)
	{
		if (!((input->x_dquote) % input->col))
		{
			ft_putchar('\n');
			input->lines_in_com++;
			input->dqlines_in_com++;
		}
	}
	input->y = get_curs_row();
	input->row = input->y;
}

void		insert_print_string(t_input *i)
{
	char	*str;
	int		len;

	if (i->flag)
	{
		len = ft_strlen(&i->line[i->x - (i->index - 1)] + 1);
		str = ft_strnew(len);
		ft_putstr(ft_strncpy(str, &i->line[i->x - i->index] + 1, len));
		free(str);
	}
	else
		ft_putstr(&i->line[i->x - (i->index - 1)]);
}
