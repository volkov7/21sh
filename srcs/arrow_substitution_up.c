/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_substitution_up.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 12:44:17 by nriker            #+#    #+#             */
/*   Updated: 2020/08/08 14:51:51 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void			arrow_substitution_up_qt(t_input *input)
{
	input->y = get_curs_row();
	input->next->dflag = input->next->sub_qt;
	input->next->save_x = input->next->x;
}

void			arrow_substitution_up_not_qt(t_input *input)
{
	if ((input->next->x % input->next->col == 1)
			&& input->next->x == input->next->width)
		ft_putchar('\n');
	return_curstox(input->next);
}

t_input			*arrow_substitution_up(t_input *input)
{
	clear_last_input(input);
	print_history(input->next, input->next->line, 0);
	input->next->row = get_curs_row();
	input->next->flag = 1;
	if (!input->next->qt)
		arrow_substitution_up_not_qt(input);
	else
		arrow_substitution_up_qt(input);
	return (input->next);
}
