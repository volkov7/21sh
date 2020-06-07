/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_five.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 19:02:19 by jsance            #+#    #+#             */
/*   Updated: 2019/11/03 16:09:42 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	precision_on_dot(char *copy, size_t precision)
{
	size_t	i;

	precision--;
	if (copy[precision] != '9')
		copy[precision] += 1;
	else
	{
		i = 0;
		while (copy[precision - i] == '9')
		{
			copy[precision - i] = '0';
			i++;
			if (copy[precision - i] == '.')
				i++;
		}
		copy[precision - i] += 1;
	}
}

void	more_five(char *copy, size_t precision)
{
	size_t	i;

	if (copy[precision] == '.')
		precision_on_dot(copy, precision);
	else if (copy[precision] != '9')
		copy[precision] += 1;
	else
	{
		i = 0;
		while (copy[precision - i] == '9')
		{
			copy[precision - i] = '0';
			i++;
			if (copy[precision - i] == '.')
				i++;
		}
		copy[precision - i] += 1;
	}
}
