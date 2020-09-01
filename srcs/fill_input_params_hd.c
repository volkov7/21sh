/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_input_params_hd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 06:12:04 by nriker            #+#    #+#             */
/*   Updated: 2020/08/02 06:12:11 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		fill_input_params_hd(t_input *input)
{
	input->x = get_curs_col();
	input->y = get_curs_row();
	if (input->hdoc == 1)
		input->index = 3;
	else if (input->hdoc == 2)
		input->index = 10;
	input->width = (ft_strlen(input->line) - 1) + input->index;
}
