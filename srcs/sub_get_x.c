/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_get_x.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 13:59:07 by nriker            #+#    #+#             */
/*   Updated: 2020/03/10 11:32:02 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int         flag_3(t_input *input)
{
	int len;

	len = 0;
	// ft_printf("%d", input->c);
	if (input->dflag != 1)
 	{
		// ft_printf("0v");
		if (input->line[input->x - 9] == '\n'
			&& input->line[input->x - 10] == '\n')
		{
			// ft_printf("5v");
			return (1);
		}
		// else
		// {
		// 	ft_printf("%c", input->line[input->c - 8]);
		// }
        while (input->c >= 8)
        {
            len++;
            if (input->line[input->c - 8] == '\n')
			{
				// ft_printf("W%dW", len);
				// input->sub_qt--;
				// ft_printf("1v %d", !(len % input->col) ? input->col : len % input->col);
				return (!(len % input->col) ? input->col : len % input->col);
 			}
			input->c--;
		// ft_printf("%d %d %d", input->c, len, input->x);
		}
	}
	else
	{
		len = 8;
		while (input->c-- >= 8)
			len++;
		// ft_printf("2v %d", !(len % input->col) ? input->col : len % input->col);
		return (!(len % input->col) ? input->col : len % input->col);
	}
	// ft_printf("3v");
	return (0);
}

int			sub_get_x(t_input *input, int flag)
{
	/*
	** flag = 1 - pressed up; 2 - pressed down; 3 - pressed left;
	*/
	input->c = input->x - 2;
	if (flag == 3)
		return (flag_3(input));
	return (0);
}
