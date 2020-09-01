/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pressed_prev_word.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 20:37:50 by nriker            #+#    #+#             */
/*   Updated: 2020/08/05 20:25:02 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		set_cursor_prev_2(int *x, t_input *input)
{
	int		xt;

	xt = get_curs_col();
	while ((*x) && input->line[*x] != ' ')
	{
		if ((xt % input->col) == 1)
		{
			ft_putstr("\e[1A");
			ft_printf("\e[%dG", input->col);
			input->y--;
			xt = input->col;
		}
		else
		{
			ft_putstr("\e[1D");
			xt--;
		}
		if (input->quote)
			input->x_quote--;
		else if (input->dquote)
			input->x_dquote--;
		input->x--;
		(*x)--;
	}
}

void		set_cursor_prev_1(int *x, t_input *input)
{
	int		xt;

	xt = get_curs_col();
	while ((*x) && input->line[*x] == ' ')
	{
		if ((xt % input->col) == 1)
		{
			ft_putstr("\e[1A");
			ft_printf("\e[%dG", input->col);
			input->y--;
			xt = input->col;
		}
		else
		{
			ft_putstr("\e[1D");
			xt--;
		}
		if (input->quote)
			input->x_quote--;
		else if (input->dquote)
			input->x_dquote--;
		input->x--;
		(*x)--;
	}
}

void		set_cursor_prev_word(int x, t_input *input)
{
	if ((size_t)x == ft_strlen(input->line))
		x--;
	if (input->line[x] == ' ')
	{
		set_cursor_prev_1(&x, input);
	}
	else if (input->line[x] != ' ')
	{
		set_cursor_prev_2(&x, input);
		set_cursor_prev_1(&x, input);
	}
}

void		pressed_prev_word(t_input *input)
{
	if (!ft_strlen(input->line))
		return ;
	if (!input->qt)
		set_cursor_prev_word(input->x - input->index, input);
}
