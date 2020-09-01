/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_history_qt_between_x.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 21:00:21 by nriker            #+#    #+#             */
/*   Updated: 2020/08/08 16:26:29 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		delete_history_qt_between_x_col(t_input *input)
{
	input->y = get_curs_row();
	input->y--;
	ft_printf("\e[%d;%dH", input->y, input->col);
	ft_putstr("\e[J");
	print_history(input->next, &input->line[input->x - input->index], 0);
	ft_printf("\e[%d;%dH", input->y, input->col);
	input->x_quote = input->col;
}

void		delete_history_qt_between_x_not_col(t_input *input)
{
	input->y = get_curs_row();
	input->x_quote = get_curs_col() - 1;
	ft_putstr("\e[1D");
	ft_putstr("\e[J");
	print_history(input->next, &input->line[input->x - input->index], 0);
	ft_printf("\e[%d;%dH", input->y, input->x_quote);
}

void		delete_history_qt_between_x_n(t_input *input)
{
	input->y = get_curs_row();
	input->y--;
	if (input->dflag > 0)
		input->dflag--;
	if (input->sub_qt > 0)
		input->sub_qt--;
	input->x_quote = sub_get_x(input, 3);
	ft_printf("\e[%d;%dH", input->y, input->x_quote);
	ft_putstr("\e[J");
	print_history(input->next, &input->line[input->x - input->index], 0);
	ft_printf("\e[%d;%dH", input->y, input->x_quote);
	input->qlines_in_com--;
	input->lines_in_com--;
}

void		delete_history_qt_between_x(t_input *input)
{
	if (input->qt && input->line[input->x - (input->index + 1)] == '\n')
		delete_history_qt_between_x_n(input);
	else if (input->x_quote % input->col == 1)
		delete_history_qt_between_x_col(input);
	else
		delete_history_qt_between_x_not_col(input);
}
