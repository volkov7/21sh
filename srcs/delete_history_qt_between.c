/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_history_qt_between.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 20:55:44 by nriker            #+#    #+#             */
/*   Updated: 2020/08/08 16:26:18 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		delete_history_qt_between_width_col(t_input *input)
{
	ft_putstr("\e[1P");
	ft_putstr("\e[1A");
	ft_printf("\e[%dG", input->col);
	input->x_quote = input->col;
	input->y--;
}

void		delete_history_qt_between_width_n(t_input *input)
{
	input->y = get_curs_row();
	ft_putstr("\e[1A");
	input->dflag--;
	input->x_quote = sub_get_x(input, 3);
	ft_printf("\e[%dG", input->x_quote);
	input->y--;
	input->sub_qt--;
	input->lines_in_com--;
}

void		delete_history_qt_between_width(t_input *input)
{
	if (input->line[input->x - (input->index + 1)] == '\n')
	{
		delete_history_qt_between_width_n(input);
	}
	else if (input->x_quote % input->col == 1)
	{
		delete_history_qt_between_width_col(input);
	}
	else
	{
		ft_putstr("\e[1D");
		input->x_quote--;
	}
	ft_putstr("\e[1P");
}

void		delete_history_qt_between(t_input *input)
{
	if (input->x == input->width)
	{
		delete_history_qt_between_width(input);
	}
	else if ((input->flag && input->qt && input->x > input->index))
	{
		delete_history_qt_between_x(input);
	}
	input->x--;
	input->width--;
	input->width_dquote--;
	if (!(input->width % input->col))
	{
		input->lines_in_com--;
		input->row--;
	}
	input->line = lineremove(input->line, input->x - input->index);
}
