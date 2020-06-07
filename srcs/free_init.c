/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 08:19:56 by nriker            #+#    #+#             */
/*   Updated: 2020/02/13 09:19:03 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		free_init(t_init *in)
{
	int		i;

	i = -1;
	if (in->input)
	{
		free_input(in->input);
	}
	// if (in->terminal)
	// 	free(in->terminal);
	// if (in->list)
	// 	while (in->list[++i])
	// 		free(in->list[i]);
	// if (in->list)
	// 	free(in->list);
}
