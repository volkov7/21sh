/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pressed_home.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 20:29:12 by nriker            #+#    #+#             */
/*   Updated: 2020/08/01 20:37:45 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		set_cursor_in_home(int len, t_input *input)
{
	int x;

	x = get_curs_col();
	while (len--)
	{
		if ((x % input->col) == 1)
		{
			ft_putstr("\e[1A");
			ft_printf("\e[%dG", input->col);
			input->y--;
			x = input->col;
		}
		else
		{
			ft_putstr("\e[1D");
			x--;
		}
		if (input->quote)
			input->x_quote--;
		else if (input->dquote)
			input->x_dquote--;
		input->x--;
	}
}

void		pressed_home(t_input *input)
{
	if (!input->qt)
		set_cursor_in_home(input->x - input->index, input);
	else if (input->quote && !input->flag)
		set_cursor_in_home(input->x_quote - 8, input);
	else if (input->dquote && !input->flag)
		set_cursor_in_home(input->x_dquote - 9, input);
}
