/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle_first_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 06:54:08 by nriker            #+#    #+#             */
/*   Updated: 2020/08/01 19:17:56 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"
#include "lexer.h"

void		return_input_command(t_init *in, t_input *input, t_envlist *envlst)
{
	ft_putchar('\n');
	input->line = lineadd(&input->line, '\n', input->width - input->index);
	if (input->pressed_ctrl_d)
		input->pressed_ctrl_d = 0;
	else
		prepare_lexer(input->line, &envlst, in, input);
}

t_input		*cycle_first_input(t_init *in)
{
	t_input			*input;
	t_envlist		*envlst;

	envlst = get_envlst(0);
	while (1)
	{
		input = create_input();
		get_input(input);
		input = read_input(in, input);
		input = get_input(0);
		if (ft_strlen(input->line) && ft_strcmp(input->line, "\n")
			&& !check_command(input))
		{
			return_input_command(in, input, envlst);
			return (input);
		}
		free_input(input);
		ft_putstr("\n21sh%> ");
	}
}
