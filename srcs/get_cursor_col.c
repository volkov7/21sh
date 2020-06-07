/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cursor_col.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 13:29:05 by nriker            #+#    #+#             */
/*   Updated: 2020/02/14 13:40:46 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			get_curs_col(void)
{
	size_t		i;
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
	i = 1;
	get[l] = '\0';
	// while (get[i - 1] != ';' && get[i] != '\0')
	// 	i++;

	// ft_printf("q%cq", *(ft_strrchr(get, ';') + 1));

	// if (ft_isdigit(*(ft_strrchr(get, ';') + 1)) == false)
	// 	return (-1);
	row = ft_atoi(ft_strrchr(get, ';') + 1);
	return (row);
}
