/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_get_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 13:59:07 by nriker            #+#    #+#             */
/*   Updated: 2020/08/02 06:04:08 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			flag_3(t_input *input)
{
	int len;

	len = 0;
	if (input->dflag != 1)
	{
		if (input->line[input->x - 9] == '\n'
			&& input->line[input->x - 10] == '\n')
			return (1);
		while (input->c >= 8)
		{
			len++;
			if (input->line[input->c - 8] == '\n')
				return (!(len % input->col) ? input->col : len % input->col);
			input->c--;
		}
	}
	else
	{
		len = 8;
		while (input->c-- >= 8)
			len++;
		return (!(len % input->col) ? input->col : len % input->col);
	}
	return (0);
}

int			sub_get_x(t_input *input, int flag)
{
	input->c = input->x - 2;
	if (flag == 3)
		return (flag_3(input));
	return (0);
}
