/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_left.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 19:24:55 by nriker            #+#    #+#             */
/*   Updated: 2020/08/05 21:02:08 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		standart_left(t_input *input)
{
	if ((!input->qt
		&& input->x % input->col == 1)
		|| (input->x_quote % input->col == 1)
		|| (input->x_dquote % input->col == 1))
	{
		ft_putstr("\e[1A");
		ft_printf("\e[%dG", input->col);
		input->y--;
	}
	else
		ft_putstr("\e[1D");
	input->x--;
}

void		history_left(t_input *input)
{
	input->flag_qt = 0;
	if (input->qt && input->line[input->x - (input->index + 1)] == '\n')
	{
		input->dflag--;
		input->x_quote = sub_get_x(input, 3);
		ft_putstr("\e[1A");
		ft_printf("\e[%dG", input->x_quote);
		input->y--;
	}
	else if (input->x_quote % input->col == 1)
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

void		arrowpress_left(t_input *input, int start)
{
	if ((input->flag && input->qt && input->x > start))
		history_left(input);
	else if ((((input->x > start && !input->qt) || input->x_quote > start
			|| input->x_dquote > start) && !input->flag)
			|| (input->flag && !input->qt && input->x > start))
		standart_left(input);
	if (input->x_quote > start && !input->flag)
		input->x_quote--;
	else if (input->x_dquote > start && !input->flag)
		input->x_dquote--;
}

void		press_left(t_input *input)
{
	int		start;

	input->p_tab = 0;
	input->p_tab_part = 0;
	start = 0;
	if (input->hdoc == 1)
		start = 3;
	else if (input->hdoc == 2)
		start = 10;
	else if (!input->qt)
		start = 8;
	else if (input->qt)
		start = 8;
	arrowpress_left(input, start);
}
