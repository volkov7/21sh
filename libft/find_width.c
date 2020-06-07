/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_width.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 20:37:49 by nriker            #+#    #+#             */
/*   Updated: 2019/11/03 16:12:30 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	find_width(t_flags **f, int i)
{
	while ((*f)->right_s[++i])
		if (((*f)->right_s[i] >= '1' && (*f)->right_s[i] <= '9'))
		{
			if (i == 0)
			{
				(*f)->nr_width = ft_atoi(&(*f)->right_s[i]);
				return ;
			}
			else
			{
				if ((*f)->right_s[i - 1] == '.')
				{
					i++;
					while ((*f)->right_s[i] >= '1' && (*f)->right_s[i] <= '9')
						i++;
				}
				else if ((*f)->right_s[i - 2] != '.')
				{
					(*f)->nr_width = ft_atoi(&(*f)->right_s[i]);
					return ;
				}
			}
		}
}
