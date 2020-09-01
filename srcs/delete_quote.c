/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 21:32:28 by nriker            #+#    #+#             */
/*   Updated: 2020/08/01 21:35:08 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		delete_quote_x_col(t_input *input)
{
	ft_putstr("\e[1A");
	ft_printf("\e[%dG", input->col);
	input->y--;
	ft_putstr(&input->line[input->x - input->index]);
	ft_putchar(' ');
	ft_printf("\e[%d;%dH", input->y, input->col);
}

void		delete_quote_x_not_col(t_input *input)
{
	ft_putstr("\e[1D");
	ft_putstr(&input->line[input->x - input->index]);
	ft_putchar(' ');
	if (!(input->x_quote % input->col))
		ft_printf("\e[%d;%dH", input->y, input->col - 1);
	else
		ft_printf("\e[%d;%dH", input->y, (input->x_quote % input->col) - 1);
}

void		delete_quote_x(t_input *input)
{
	if (input->x_quote % input->col == 1)
		delete_quote_x_col(input);
	else
		delete_quote_x_not_col(input);
}

void		delete_quote_width(t_input *input)
{
	if (input->x_quote % input->col == 1)
	{
		ft_putstr("\e[1A");
		ft_printf("\e[%dG", input->col);
		input->y--;
	}
	else
		ft_putstr("\e[1D");
	ft_putstr("\e[1P");
}

void		delete_quote(t_input *input)
{
	if (input->x_quote == input->width_quote)
		delete_quote_width(input);
	else if (input->x_quote < input->width_quote)
		delete_quote_x(input);
	input->x--;
	input->width--;
	input->x_quote--;
	input->width_quote--;
	if (!(input->width_quote % input->col))
	{
		input->lines_in_qt--;
		input->lines_in_com--;
		input->qlines_in_com--;
		input->row--;
	}
	input->line = lineremove(input->line, input->x - input->index);
}
