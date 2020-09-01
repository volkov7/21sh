/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_cursor_when_ctrl_c.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 19:15:07 by nriker            #+#    #+#             */
/*   Updated: 2020/08/01 19:15:11 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"
#include "lexer.h"

t_input		*get_last_struct(t_input *input)
{
	while (input->prev != 0)
		input = input->prev;
	return (input);
}

void		free_input_one_struct(t_input *input)
{
	if (input)
	{
		if (input->line)
			free(input->line);
		if (input->ctrl_d_line)
			free(input->ctrl_d_line);
		if (input->word)
			free(input->word);
		free(input);
	}
}

void		create_input_ctrl_c(t_input *input)
{
	t_input		*next_input;

	next_input = NULL;
	if (input->prev != 0)
		input = get_last_struct(input);
	if (input->next != 0)
		next_input = input->next;
	free_input_one_struct(input);
	input = create_input();
	if (next_input != NULL)
	{
		next_input->prev = input;
		input->next = next_input;
	}
	get_input(input);
}

void		return_cursor_when_ctrl_c(t_input *input)
{
	if (input->x == input->width)
	{
		ft_putstr("\n21sh%> ");
		create_input_ctrl_c(input);
	}
	else
	{
		get_curs_pos_inend(input);
		ft_putstr("\n21sh%> ");
		create_input_ctrl_c(input);
	}
	return ;
}
