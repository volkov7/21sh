/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_lh.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 20:43:14 by nriker            #+#    #+#             */
/*   Updated: 2019/10/29 20:44:26 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		find_lh(t_flags **flags, char *s)
{
	int		i;

	i = -1;
	while (s[++i])
		if (s[i] == 'l')
			(*flags)->lsize++;
		else if (s[i] == 'h')
			(*flags)->hsize++;
	return (1);
}
