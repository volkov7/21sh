/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_dquote.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 21:40:08 by nriker            #+#    #+#             */
/*   Updated: 2020/08/01 21:41:42 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		delete_dquote_x_col(t_input *input)
{
	ft_putstr("\e[1A");
	ft_printf("\e[%dG", input->col);
	input->y--;
	ft_putstr(&input->line[input->x - 8]);
	ft_putchar(' ');
	ft_printf("\e[%d;%dH", input->y, input->col);
}

void		delete_dquote_x_not_col(t_input *input)
{
	ft_putstr("\e[1D");
	ft_putstr(&input->line[input->x - 8]);
	ft_putchar(' ');
	if (!(input->x_dquote % input->col))
		ft_printf("\e[%d;%dH", input->y, input->col - 1);
	else
		ft_printf("\e[%d;%dH", input->y, (input->x_dquote % input->col) - 1);
}

void		delete_dquote_x(t_input *input)
{
	if (input->x_dquote % input->col == 1)
		delete_dquote_x_col(input);
	else
		delete_dquote_x_not_col(input);
}

void		delete_dquote_width(t_input *input)
{
	if (input->x_dquote % input->col == 1)
	{
		ft_putstr("\e[1A");
		ft_printf("\e[%dG", input->col);
		input->y--;
	}
	else
		ft_putstr("\e[1D");
	ft_putstr("\e[1P");
}

void		delete_dquote(t_input *input)
{
	if (input->x_dquote == input->width_dquote)
		delete_dquote_width(input);
	else if (input->x_dquote < input->width_dquote)
		delete_dquote_x(input);
	input->x--;
	input->width--;
	input->x_dquote--;
	input->width_dquote--;
	if (!(input->width_dquote % input->col))
	{
		input->lines_in_qt--;
		input->lines_in_com--;
		input->dqlines_in_com--;
		input->row--;
	}
	input->line = lineremove(input->line, input->x - input->index);
}
