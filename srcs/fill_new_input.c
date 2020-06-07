/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_new_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/14 08:47:55 by nriker            #+#    #+#             */
/*   Updated: 2020/05/23 03:10:42 by root             ###   ########.fr       */
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
	return (copy);
}

void		fill_new_input(t_input *input)
{
	int		x;
	// char	*copy;
	t_input	*copy;

	if (ft_strlen(input->line) && input->flag && !check_quotes(input))
	{
		// while (1);///!!!!!!!!!!!!!!!!
		x = input->x;
		// input->flag = 1;
		input->dflag = 1;
		// copy = ft_strdup(input->line);
		copy = input;
		while (input->prev)
			input = input->prev;
		copy_struct_history(copy, input);
		
		// input->line = copy;
		// input->x = x;
		// input->row = get_curs_row();

		// if (!input->qt)
		// 	input->width = ft_strlen(input->line) + 8;
		// else
		// 	input->width = ft_strlen(input->line) + 9;
	}
}
