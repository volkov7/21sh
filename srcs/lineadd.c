/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lineadd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 20:52:56 by nriker            #+#    #+#             */
/*   Updated: 2020/08/15 14:31:44 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char		*lineadd(char **line, char c, int index)
{
	int		len;
	char	*new_line;

	if (index < 0)
		return (0);
	len = ft_strlen((*line));
	if (!(new_line = (char*)malloc(sizeof(char) * len + 2)))
		ft_error_select(3);
	ft_bzero(new_line, len + 2);
	if (!len)
		new_line[len] = c;
	else if (index == len)
	{
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
