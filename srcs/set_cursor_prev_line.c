/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_cursor_prev_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 06:24:07 by nriker            #+#    #+#             */
/*   Updated: 2020/08/02 06:32:52 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		set_cursor_prev_line_cycle(t_input *input)
{
	while (input->line[input->x - input->index] != '\n')
	{
		if (!(input->x_quote % input->col))
		{
			ft_putstr("\e[1E");
			input->x_quote = 1;
			input->y++;
		}
		else
		{
			ft_putstr("\e[1C");
			input->x_quote++;
		}
		input->x++;
	}
	ft_putstr("\e[1E");
	input->x_quote = 1;
	input->dflag++;
	input->y++;
	input->x++;
	input->c = input->len_qt;
	input->x_quote = get_curs_col();
}

void		set_cursor_prev_line(t_input *input)
{
	set_cursor_prev_line_cycle(input);
	if (input->line[input->x - input->index] == '\n')
		return ;
	while (input->c > 0 && input->x <= input->width)
	{
		if (input->line[input->x - input->index] == '\n')
			break ;
		else if (!(input->x_quote % input->col)
			&& input->line[input->x - (input->index + 1)] != '\n')
		{
			ft_putstr("\e[1E");
			input->y++;
			input->x_quote = 1;
		}
		else if (input->x < input->width)
		{
			ft_putstr("\e[1C");
			input->x_quote++;
		}
		input->c--;
		input->x++;
	}
	if (input->x > input->width)
		input->x = input->width;
	input->x_quote = get_curs_col();
}
