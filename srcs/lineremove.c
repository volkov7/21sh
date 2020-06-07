/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lineremove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 18:06:27 by nriker            #+#    #+#             */
/*   Updated: 2020/05/17 02:29:52 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// char	*lineremove_2(char*line, int index)
// {
// 	char	*new_line;
// 	int		len;

// 	// index = index - 8;
// 	if (index < 0)
// 		return (0);
// 	len = ft_strlen(line);
// 	if (!(new_line = (char*)malloc(sizeof(char) * len + 1)))
// 		ft_error_select(3);
// 	bzero(new_line, len + 1);
// 	if (index == len)
// 	{
// 		ft_strncpy(new_line, line, ft_strlen(line));
// 		free(line);
// 	}
// 	else if (index < len)
// 	{
// 		ft_strncpy(new_line, line, index + 1);
// 		ft_strcpy(&new_line[index], &line[index + 1]);
// 		free(line);
// 	}
// 	return (new_line);
// }

char	*lineremove(char *line, int index)
{
	char	*new_line;
	int		len;

	// index = index - 8;
	if (index < 0)
		return (0);
	len = ft_strlen(line);
	if (!(new_line = (char*)malloc(sizeof(char) * len + 1)))
		ft_error_select(3);
	bzero(new_line, len + 1);
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
