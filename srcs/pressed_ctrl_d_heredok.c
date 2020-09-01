/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pressed_ctrl_d_heredok.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 20:28:14 by nriker            #+#    #+#             */
/*   Updated: 2020/08/08 07:38:27 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			pressed_ctrl_d_heredok(t_input *i)
{
	if ((i->big_heredok && i->width == 10)
		|| (i->small_heredok && i->width == 3))
	{
		i->line = ft_strjoinfreefree(i->input_original->ctrl_d_line, i->line);
		free_input(i);
		exit(EXIT_FAILURE);
	}
	else
		return (1);
	return (0);
}
