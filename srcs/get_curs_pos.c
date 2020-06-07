/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_curs_pos.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 16:38:27 by nriker            #+#    #+#             */
/*   Updated: 2020/03/11 16:39:52 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		get_curs_pos_inx(t_input *input)
{
	while (input->c != input->next->x)
	{
		if (input->c % input->col == 0)
			ft_putstr("\e[1E");
		else
			ft_putstr("\e[1C");
		input->c++;
	}
}
