/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copyinput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 17:24:36 by nriker            #+#    #+#             */
/*   Updated: 2020/08/02 07:22:16 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		copyinput_all(t_input *copy, t_input *input)
{
	copy->x = input->width;
	copy->width = input->width;
	copy->quote = input->quote;
	copy->width_quote = input->width_quote;
	copy->x_quote = input->x_quote;
	copy->dquote = input->dquote;
	copy->width_dquote = input->width_dquote;
	copy->x_dquote = input->x_dquote;
	copy->qt = input->qt;
	copy->lines_in_com = input->lines_in_com;
	copy->qlines_in_com = input->qlines_in_com;
	copy->dqlines_in_com = input->dqlines_in_com;
	copy->sub_qt = input->sub_qt;
	copy->hdoc = input->hdoc;
}

t_input		*copyinput(t_input *input)
{
	t_input		*head;
	t_input		*copy;

	copy = create_input();
	head = copy;
	while (input)
	{
		if (ft_strlen(input->line))
			copy->line = ft_strdup(input->line);
		copyinput_all(copy, input);
		input = input->next;
		if (input)
		{
			copy->next = create_input();
			copy->next->prev = copy;
			copy = copy->next;
		}
	}
	return (head);
}
