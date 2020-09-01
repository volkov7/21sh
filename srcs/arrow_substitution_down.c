/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_substitution_down.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 13:10:19 by nriker            #+#    #+#             */
/*   Updated: 2020/08/02 07:06:57 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void			arrow_substitution_down_firstly(t_input *input)
{
	clear_last_input(input);
	if (input->prev->quote && !input->prev->flag)
		print_history(input->prev, input->prev->line
			+ (input->prev->width - input->prev->width_quote), 1);
	else if (input->prev->dquote && !input->prev->flag)
		print_history(input->prev, input->prev->line
			+ (input->prev->width - input->prev->width_dquote), 1);
	else if (input->prev->qt)
		check_qt(input->prev);
	else
		print_history(input->prev, input->prev->line, 1);
	input->prev->row = get_curs_row();
}

void			arrow_substitution_down_flag(t_input *input)
{
	input->prev->x_quote = get_curs_col();
	if (input->prev->qt)
		input->prev->x = input->prev->save_x;
	else
		return_curstox(input->prev);
	input->y = get_curs_row();
	input->prev->dflag = input->prev->sub_qt;
}

t_input			*arrow_substitution_down(t_input *input)
{
	arrow_substitution_down_firstly(input);
	if (input->prev->prev)
		input->prev->flag = 1;
	if ((input->prev->x % input->prev->col == 1)
		&& input->prev->x == input->width)
		ft_putchar('\n');
	if (!input->prev->flag && !input->prev->qt)
	{
		return_curstox(input->prev);
		input->prev->y = get_curs_row();
	}
	else if (!input->prev->flag && input->prev->qt)
	{
		return_curstox_qt(input->prev);
		input->prev->y = get_curs_row();
	}
	else if (input->prev->flag)
		arrow_substitution_down_flag(input);
	return (input->prev);
}
