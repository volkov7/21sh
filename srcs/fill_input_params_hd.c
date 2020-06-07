/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_input_params_hd.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/16 04:13:20 by root              #+#    #+#             */
/*   Updated: 2020/05/17 06:17:56 by root             ###   ########.fr       */
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
	// ft_printf("%d", ft_strlen(input->line));
	// while (1);
	input->width = (ft_strlen(input->line) - 1) + input->index;
}
