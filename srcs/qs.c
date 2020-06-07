/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   qs.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:46:59 by nriker            #+#    #+#             */
/*   Updated: 2020/02/11 09:20:21 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	qs_change(char **buf, int *left, int *right)
{
	char	*tmp;

	if (*left <= *right)
	{
		tmp = buf[*left];
		buf[*left] = buf[*right];
		buf[*right] = tmp;
		(*left)++;
		(*right)--;
	}
}

void		qs(char **buf, int size, int first, int last)
{
	int		left;
	int		right;
	char	*middle;

	if (first < last)
	{
		left = first;
		right = last;
		middle = buf[(first + last) / 2];
		while (left <= right)
		{
			while (ft_strcmp(buf[left], middle) < 0)
				left++;
			while (ft_strcmp(buf[right], middle) > 0)
				right--;
			qs_change(buf, &left, &right);
		}
		qs(buf, size, first, right);
		qs(buf, size, left, last);
	}
}
