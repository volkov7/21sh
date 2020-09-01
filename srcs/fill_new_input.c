/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_new_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 06:09:59 by nriker            #+#    #+#             */
/*   Updated: 2020/08/05 20:21:25 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_input		*copy_struct_history(t_input *copy, t_input *input)
{
	if (input->line)
		free(input->line);
	input->line = ft_strdup(copy->line);
	input->width = copy->width;
	input->x = copy->width;
	input->quote = copy->quote;
	input->width_quote = copy->width_quote;
	input->x_quote = copy->width_quote;
	input->dquote = copy->dquote;
	input->width_dquote = copy->width_dquote;
	input->qt = copy->qt;
	input->lines_in_com = copy->lines_in_com;
	input->qlines_in_com = copy->qlines_in_com;
	input->dqlines_in_com = copy->dqlines_in_com;
	input->sub_qt = copy->sub_qt;
	input->pressed_ctrl_d = copy->pressed_ctrl_d;
	return (copy);
}

void		fill_new_input(t_input *input)
{
	t_input	*copy;

	if (ft_strlen(input->line) && input->flag && !check_quotes(input))
	{
		input->dflag = 1;
		copy = input;
		while (input->prev)
			input = input->prev;
		copy_struct_history(copy, input);
	}
}
