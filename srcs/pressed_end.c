/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pressed_end.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 20:35:39 by nriker            #+#    #+#             */
/*   Updated: 2020/08/01 20:38:07 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		set_cursor_in_end(int len, int width, t_input *input)
{
	int	x;

	x = get_curs_col();
	while (len < width)
	{
		if (!(x % input->col))
		{
			ft_putstr("\e[1E");
			input->y++;
			x = 0;
		}
		else
			ft_putstr("\e[1C");
		x++;
		len++;
		if (input->quote)
			input->x_quote++;
		else if (input->dquote)
			input->x_dquote++;
		input->x++;
	}
}

void		pressed_end(t_input *input)
{
	if (!input->qt)
		set_cursor_in_end(input->x, input->width, input);
	else if (input->quote && !input->flag)
		set_cursor_in_end(input->x_quote, input->width_quote, input);
	else if (input->dquote && !input->flag)
		set_cursor_in_end(input->x_dquote, input->width_dquote, input);
}
