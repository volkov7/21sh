/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cursor_col.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:29:05 by nriker            #+#    #+#             */
/*   Updated: 2020/08/05 20:17:42 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			get_curs_col(void)
{
	size_t		l;
	int			row;
	char		get[50];

	l = 0;
	write(STDIN_FILENO, GETCURSORPOS, 4);
	while (l < 50 - 1 && read(1, get + l, 1) == 1)
	{
		if (get[l] == 'R')
			break ;
		l++;
	}
	get[l] = '\0';
	row = ft_atoi(ft_strrchr(get, ';') + 1);
	return (row);
}
