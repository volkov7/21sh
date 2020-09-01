/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_substitution_qt.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:19:08 by nriker            #+#    #+#             */
/*   Updated: 2020/08/15 15:03:33 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			get_len_next_line_qt(t_input *i)
{
	int len;

	len = 0;
	i->x_quote = get_curs_col();
	i->c = i->x;
	while (i->c > i->index && i->line[i->c - (i->index + 1)] != '\n')
	{
		if (i->x_quote % i->col == 1)
			i->x_quote = i->col;
		else
			i->x_quote--;
		i->c--;
		len++;
	}
	return (len);
}

int			get_len_of_line(t_input *i)
{
	int len;

	len = 0;
	i->c = i->x;
	if (i->line[i->c - i->index] == '\n')
	{
		len++;
		i->c--;
	}
	while (i->line[i->c - (i->index + 1)] != '\n' && i->c != i->index)
	{
		len++;
		i->c--;
	}
	return (len);
}

void		up_sub_qt(t_input *input)
{
	input->x_quote = get_curs_col();
	if (!input->flag_qt)
	{
		input->len_qt = get_len_of_line(input);
	}
	input->flag_qt = 1;
	set_cursor_next_line(input);
}

void		down_sub_qt(t_input *input)
{
	input->x_quote = get_curs_col();
	if (!input->flag_qt)
	{
		input->len_qt = get_len_of_line(input);
	}
	input->flag_qt = 1;
	set_cursor_prev_line(input);
}
