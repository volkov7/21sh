/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enter_press.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 18:35:19 by nriker            #+#    #+#             */
/*   Updated: 2020/08/08 16:26:45 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		enter_press_set_qt_dquote(t_input *input)
{
	ft_printf("\e[%d;%dH", input->row, input->width % input->col);
	ft_putstr("\ndquote> ");
	if (input->row < tgetnum("li"))
		input->row++;
	input->y = input->row;
	input->x_quote = 0;
	input->width_quote = 0;
	input->x_dquote = 9;
	input->width_dquote = 9;
	input->old_row = 0;
	input->old = 0;
	input->o = 0;
	input->f = 0;
}

void		enter_press_set_qt_quote(t_input *input)
{
	ft_putstr("\nquote> ");
	if (input->row < input->col)
		input->row++;
	input->y = input->row;
	input->x_quote = 8;
	input->width_quote = 8;
	input->width_dquote = 0;
	input->old_row = 0;
	input->old = 0;
	input->o = 0;
	input->f = 0;
}

void		enter_press_set_qt(t_input *input)
{
	input->qt = 1;
	input->flag = 0;
	input->x = input->width;
	input->line = lineadd(&input->line, '\n', input->x - input->index);
	input->x++;
	input->width++;
	input->lines_in_qt = 1;
	input->qlines_in_com = 1;
	input->dqlines_in_com = 1;
	input->lines_in_com++;
	input->sub_qt++;
}

void		enter_press_qt(t_input *input)
{
	enter_press_set_qt(input);
	if (input->quote)
		enter_press_set_qt_quote(input);
	else if (input->dquote)
		enter_press_set_qt_dquote(input);
}

int			enter_press(t_input *input, char buf[7])
{
	if ((buf[0] == 13 || buf[0] == 10) && !buf[1])
	{
		fill_new_input(input);
		get_curs_pos_inend(input);
		if (!check_quotes(input))
		{
			if (input->hdoc)
				enter_press_heredok(input);
			return (0);
		}
		enter_press_qt(input);
	}
	return (1);
}
