/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_cycle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 00:08:49 by nriker            #+#    #+#             */
/*   Updated: 2020/08/05 20:23:39 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"
#include "lexer.h"

int			check_command(t_input *input)
{
	int		len;
	int		x;

	x = -1;
	len = ft_strlen(input->line);
	while (++x < len)
		if (input->line[x] != ' ' && input->line[x] != '\n')
			return (0);
	return (1);
}

void		main_cycle(t_init *in, t_input *input)
{
	while (1)
	{
		ft_putstr("21sh%> ");
		if (!input)
			input = cycle_first_input(in);
		else
		{
			input = cycle_other_input(in, input);
		}
	}
}
