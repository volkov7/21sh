/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_right.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 19:35:57 by nriker            #+#    #+#             */
/*   Updated: 2020/08/05 20:32:42 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		standart_right(t_input *input)
{
	if ((!input->qt && !(input->x % input->col))
		|| (input->quote && !(input->x_quote % input->col))
		|| (input->dquote && !(input->x_dquote % input->col)))
	{
		ft_putstr("\e[1E");
		input->y++;
	}
	else
		ft_putstr("\e[1C");
	input->x++;
}

void		history_right(t_input *input)
{
	input->flag_qt = 0;
	if (input->line[input->x - 8] == '\n')
	{
		ft_putstr("\e[1E");
		input->x_quote = 1;
		input->dflag++;
		input->y++;
	}
	else if (!(input->x_quote % input->col))
	{
		ft_putstr("\e[1E");
		input->x_quote = 1;
		input->y++;
	}
	else
	{
		ft_putstr("\e[1C");
		input->x_quote++;
	}
	input->x++;
}

void		arrowpress_right(t_input *input)
{
	if (input->flag && input->qt && input->x < input->width)
		history_right(input);
	else if (((!input->qt && input->x < input->width))
		|| (!input->flag
			&& input->quote && input->x_quote < input->width_quote)
		|| (!input->flag
			&& input->x_dquote && input->x_dquote < input->width_dquote)
		|| (input->flag && !input->qt && input->x < input->width))
		standart_right(input);
	if (input->quote && input->x_quote < input->width_quote
		&& !input->flag)
		input->x_quote++;
	else if (input->x_dquote && input->x_dquote < input->width_dquote
		&& !input->flag)
		input->x_dquote++;
}

void		press_right(t_input *input)
{
	input->p_tab = 0;
	input->p_tab_part = 0;
	arrowpress_right(input);
}
