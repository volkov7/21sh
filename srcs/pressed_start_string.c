/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pressed_start_string.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 21:07:09 by nriker            #+#    #+#             */
/*   Updated: 2020/08/01 20:38:54 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		pressed_start_string(t_input *input)
{
	int		cursor;

	cursor = get_curs_col();
	if (!input->heredok)
	{
		if (!input->qt)
		{
			if (input->x > input->col)
			{
				ft_printf("\e[%dG", 1);
				input->x = input->x - cursor + 1;
			}
			else
			{
				ft_printf("\e[%dG", 8);
				input->x = 8;
			}
		}
	}
}
