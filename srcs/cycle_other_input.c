/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_other_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 13:11:37 by nriker            #+#    #+#             */
/*   Updated: 2020/08/05 20:24:19 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"
#include "lexer.h"

void		right_command(t_init *in, t_input *input, t_envlist *envlst)
{
	ft_putchar('\n');
	if (input->line[input->x - 8] != '\n')
		input->line = lineadd(&input->line, '\n', input->width - input->index);
	if (input->pressed_ctrl_d)
		input->pressed_ctrl_d = 0;
	else
		prepare_lexer(input->line, &envlst, in, input);
}

t_input		*return_copy_input(t_init *in, t_input *input)
{
	input->prev = create_input();
	input->prev->next = input;
	input = input->prev;
	in->input = input;
	return (copyinput(input));
}

void		return_command(t_init *in, t_input *input, t_input *copy,
					t_envlist *envlst)
{
	if (!input->pressed_ctrl_d)
		copy_struct_history(copy, input);
	free_input(copy);
	ft_putchar('\n');
	if (input->line[input->x - 8] != '\n')
		input->line = lineadd(&input->line, '\n', input->width - input->index);
	if (input->pressed_ctrl_d)
		input->pressed_ctrl_d = 0;
	else
		prepare_lexer(input->line, &envlst, in, input);
}

t_input		*cycle_other_input(t_init *in, t_input *input)
{
	t_input			*copy;
	t_envlist		*envlst;

	envlst = get_envlst(0);
	input->prev = create_input();
	input->prev->next = input;
	input = input->prev;
	in->input = input;
	copy = copyinput(input);
	while (1)
	{
		get_input(copy);
		copy = read_input(in, copy);
		copy = get_input(0);
		if (ft_strlen(copy->line) && ft_strcmp(copy->line, "\n")
			&& !check_command(copy))
		{
			return_command(in, input, copy, envlst);
			break ;
		}
		free_input(copy);
		copy = copyinput(input);
		ft_putstr("\n21sh%> ");
	}
	return (input);
}
