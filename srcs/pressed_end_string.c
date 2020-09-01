/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pressed_end_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 21:12:57 by nriker            #+#    #+#             */
/*   Updated: 2020/07/29 21:13:39 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		pressed_end_string(t_input *input)
{
	int cursor;

	if (!input->qt)
	{
		cursor = get_curs_col();
		if (((input->width - input->x) + cursor) >= input->col)
			ft_printf("\e[%dG", input->col);
		else
			ft_printf("\e[%dG", input->width % input->col);
		input->x = input->x + (get_curs_col() - cursor);
	}
}
