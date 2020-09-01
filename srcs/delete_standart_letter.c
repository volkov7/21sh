/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_standart_letter.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 21:18:26 by nriker            #+#    #+#             */
/*   Updated: 2020/08/01 21:22:00 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		delete_letter_x_not_col(t_input *input)
{
	char	*str;

	ft_putstr("\e[1D");
	if (ft_strchr(input->line, '\n'))
	{
		str = ft_strcut(input->line, '\n');
		ft_putstr(&str[input->x - input->index]);
		free(str);
	}
	else
		ft_putstr(&input->line[input->x - input->index]);
	ft_putchar(' ');
	if (!(input->x % input->col))
		ft_printf("\e[%d;%dH", input->y, input->col - 1);
	else
		ft_printf("\e[%d;%dH", input->y, (input->x % input->col) - 1);
}

void		delete_letter_x_col(t_input *input)
{
	char	*str;

	ft_putstr("\e[1A");
	ft_printf("\e[%dG", input->col);
	input->y--;
	if (input->flag)
	{
		str = ft_strcut(input->line, '\n');
		ft_putstr(&str[input->x - input->index]);
		free(str);
	}
	else
		ft_putstr(&input->line[input->x - input->index]);
	ft_putchar(' ');
	ft_printf("\e[%d;%dH", input->y, input->col);
}

void		delete_letter_x(t_input *input)
{
	if (input->x % input->col == 1)
		delete_letter_x_col(input);
	else
		delete_letter_x_not_col(input);
}

void		delete_letter_width(t_input *input)
{
	if (input->x % input->col == 1)
	{
		ft_putstr("\e[1A");
		ft_printf("\e[%dG", input->col);
		input->y--;
	}
	else
		ft_putstr("\e[1D");
	ft_putstr("\e[1P");
}

void		delete_letter(t_input *input)
{
	if (input->x == input->width)
		delete_letter_width(input);
	else if (input->x < input->width)
		delete_letter_x(input);
	input->x--;
	input->width--;
	if (!(input->width % input->col))
	{
		input->lines_in_com--;
		input->row--;
	}
	input->line = lineremove(input->line, input->x - input->index);
}
