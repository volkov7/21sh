/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_cursor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 05:58:01 by nriker            #+#    #+#             */
/*   Updated: 2020/08/02 05:58:03 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			get_curs_pos_inend(t_input *input)
{
	int		x;

	x = get_curs_col();
	input->c = input->x;
	while (input->c < input->width)
	{
		if (input->line[input->c - input->index] == '\n' || !(x % input->col))
		{
			ft_putstr("\e[1E");
			x = 1;
		}
		else
		{
			x++;
			ft_putstr("\e[1C");
		}
		input->c++;
	}
	return (input->c);
}

void		return_curstox(t_input *input)
{
	int x;

	x = get_curs_col();
	if (input->x == input->width_dquote)
		return ;
	input->c = input->width;
	while (input->c > input->x && input->c > input->index)
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
}
