/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_cursor_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 09:41:18 by nriker            #+#    #+#             */
/*   Updated: 2020/05/04 14:04:13 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void			in_quote(t_input *input)
{
	int x;

	x = get_curs_col();
	input->c = input->width_quote;
	while (input->c > input->x_quote && input->c > 8)
	{
		if (x % input->col == 1)
		{
			ft_putstr("\e[1A");
			ft_printf("\e[%dG", input->col);
			x = input->col;
		}
		else
		{
			ft_putstr("\e[1D");
			x--;
		}
		input->c--;
	}
	input->y = get_curs_row();
	// ft_putstr("\e[1D");
	// ft_printf("%d %d", input->width, input->width_quote);
	// while (1);
}

void			in_dquote(t_input *input)
{
	int x;

	x = get_curs_col();
	input->c = input->width_dquote;
	while (input->c > input->x_dquote && input->c > 9)
	{
		if (x % input->col == 1)
		{
			ft_putstr("\e[1A");
			ft_printf("\e[%dG", input->col);
			x = input->col;
		}
		else
		{
			ft_putstr("\e[1D");
			x--;
		}
		input->c--;
	}
	input->y = get_curs_row();
}

void			return_curstox_qt(t_input *input)
{
	if (input->quote)
	{
		in_quote(input);
	}
	else if (input->dquote)
	{
		in_dquote(input);
	}
}
