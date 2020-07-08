/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_cursor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/13 08:48:16 by nriker            #+#    #+#             */
/*   Updated: 2020/07/04 12:53:34 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

/*
** Function return_curstostart_str let change only cursor.
*/

// void		return_curstostart_str(t_input *input, int x)
// {
// 	int		y;
// 	int		save_x;
// 	int		save_y;
// 	int		save_c;
// 	int		save_dflag;

// 	save_x = input->x;
// 	save_y = input->y;
// 	save_c = input->c;
// 	save_dflag = input->dflag;
// 	y = get_curs_col();
// 	input->x = x;
// 	while (input->x > 8)
// 	{
// 		if (input->line[input->x - 9] == '\n')
// 		{
// 			input->dflag--;
// 			y = sub_get_x(input, 3);
// 			ft_putstr("\e[1A");
// 			ft_printf("\e[%dG", y);
// 			input->y--;
// 		}
// 		else if ((y % input->col == 1) )
// 		{
// 			// ft_putchar('Q');
// 			// ft_putchar(input->line[input->x - 9]);
// 			// while (1);
// 			ft_putstr("\e[1A");
// 			ft_printf("\e[%dG", input->col);
// 			y = input->col;
// 			input->y--;
// 			// input->x--;
// 		}
// 		else
// 		{
// 			// ft_putchar('W');
// 			ft_putstr("\e[1D");
// 			y--;
// 		}
// 		input->x--;
// 	}
// 	// input->x = get_curs_col();
// 	// input->x = save_x;
// 	input->y = save_y;
// 	input->c = save_c;
// 	input->dflag = save_dflag;
// }

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
	// ft_printf("%d", input->width);
	// while (1);
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
	// input->y = get_curs_row();
	// fill_curs_params(input);
}
