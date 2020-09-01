/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cursor_next_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 06:28:47 by nriker            #+#    #+#             */
/*   Updated: 2020/08/02 06:30:36 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		set_cursor_next_line_2(t_input *input)
{
	while ((input->x - (input->index + 1))
		&& input->line[input->x - (input->index + 1)] != '\n')
	{
		if (input->x_quote % input->col == 1)
		{
			ft_putstr("\e[1A");
			ft_printf("\e[%dG", input->col);
			input->x_quote = input->col;
			input->y--;
		}
		else
		{
			ft_putstr("\e[1D");
			input->x_quote--;
		}
		input->x--;
	}
	input->dflag--;
	input->x_quote = sub_get_x(input, 3);
	ft_putstr("\e[1A");
	ft_printf("\e[%dG", input->x_quote % input->col);
	input->y--;
	input->x--;
	input->c = get_len_next_line_qt(input);
	input->x_quote = get_curs_col();
}

void		set_cursor_next_line(t_input *input)
{
	set_cursor_next_line_2(input);
	if (input->c <= input->len_qt)
		return ;
	input->c -= input->len_qt;
	while (input->c > 0 && input->x > input->index)
	{
		if (input->x_quote % input->col == 1)
		{
			ft_putstr("\e[1A");
			ft_printf("\e[%dG", input->col);
			input->x_quote = input->col;
			input->y--;
		}
		else
		{
			ft_putstr("\e[1D");
			input->x_quote--;
		}
		input->c--;
		input->x--;
	}
	input->c = input->len_qt;
	input->x_quote = get_curs_col();
}
