/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pressed_clear_window.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/29 20:19:29 by nriker            #+#    #+#             */
/*   Updated: 2020/08/09 13:52:02 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		pressed_clear_window(t_input *input)
{
	if (!input->qt)
	{
		ft_printf("\e[1H");
		ft_printf("\e[J");
		ft_putstr("21sh%> ");
		if (input->flag)
			print_history(input, input->line, 0);
		else
			ft_putstr(input->line);
		return_curstox(input);
		input->x = get_curs_col();
		input->y = get_curs_row();
	}
}
