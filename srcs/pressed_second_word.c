/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pressed_second_word.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 20:46:20 by nriker            #+#    #+#             */
/*   Updated: 2020/07/29 20:48:36 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		set_cursor_second_2(int *x, int width, t_input *input)
{
	int	xt;

	xt = get_curs_col();
	while (((*x) < width) && input->line[*x] != ' ')
	{
		if (!(xt % input->col))
		{
			ft_putstr("\e[1E");
			input->y++;
			xt = 0;
		}
		else
			ft_putstr("\e[1C");
		xt++;
		(*x)++;
		if (input->quote)
			input->x_quote++;
		else if (input->dquote)
			input->x_dquote++;
		input->x++;
	}
}

void		set_cursor_second_1(int *x, int width, t_input *input)
{
	int	xt;

	xt = get_curs_col();
	while (((*x) < width) && input->line[*x] == ' ')
	{
		if (!(xt % input->col))
		{
			ft_putstr("\e[1E");
			input->y++;
			xt = 0;
		}
		else
			ft_putstr("\e[1C");
		xt++;
		(*x)++;
		if (input->quote)
			input->x_quote++;
		else if (input->dquote)
			input->x_dquote++;
		input->x++;
	}
}

void		set_cursor_second_word(int x, int width, t_input *input)
{
	if (input->line[x] == ' ')
	{
		set_cursor_second_1(&x, width, input);
	}
	else if (input->line[x] != ' ')
	{
		set_cursor_second_2(&x, width, input);
		set_cursor_second_1(&x, width, input);
	}
}

void		pressed_second_word(t_input *input)
{
	int		width;

	if (!ft_strlen(input->line))
		return ;
	if (!input->qt)
	{
		width = input->width - input->index;
		set_cursor_second_word(input->x - input->index, width, input);
	}
}
