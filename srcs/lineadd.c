/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lineadd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 16:51:51 by nriker            #+#    #+#             */
/*   Updated: 2020/05/16 05:14:36 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char		*lineadd(char **line, char c, int index)
{
	int		len;
	char	*new_line;

	// index = index - 8;
	if (index < 0)
		return (0);
	len = ft_strlen((*line));
	if (!(new_line = (char*)malloc(sizeof(char) * len + 2)))
		ft_error_select(3);
	bzero(new_line, len + 2);
	if (!len)
		new_line[len] = c;
	else if (index == len)
	{
		// ft_putstr("q");
		ft_strcpy(new_line, (*line));
		new_line[len] = c;
	}
	else if (index < len)
	{
		ft_strncpy(new_line, (*line), index);
		new_line[index] = c;
		ft_strcpy(&new_line[index + 1], &(*line)[index]);
	}
	free((*line));
	return (new_line);
}
