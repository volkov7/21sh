/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lineremove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 06:55:07 by nriker            #+#    #+#             */
/*   Updated: 2020/08/15 14:31:30 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char	*lineremove(char *line, int index)
{
	char	*new_line;
	int		len;

	if (index < 0)
		return (0);
	len = ft_strlen(line);
	if (!(new_line = (char*)malloc(sizeof(char) * len + 1)))
		ft_error_select(3);
	ft_bzero(new_line, len + 1);
	if (index + 1 == len)
	{
		ft_strncpy(new_line, line, ft_strlen(line) - 1);
		free(line);
	}
	else if (index < len)
	{
		ft_strncpy(new_line, line, index);
		ft_strcpy(&new_line[index], &line[index + 1]);
		free(line);
	}
	return (new_line);
}
