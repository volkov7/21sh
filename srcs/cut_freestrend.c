/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut_freestrend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 10:49:22 by nriker            #+#    #+#             */
/*   Updated: 2020/02/13 09:53:43 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char		*cut_freestrend(char **line)
{
    int		i;
    int		j;
    char	*copy;

	i = -1;
	j = -1;
	while ((*line)[++i])
		if ((*line)[i] != ' ' && (*line)[i] != '\t')
			j = i;
	if (j == -1)
		return (0);
	j++;
	copy = ft_strnew(j);
	copy = ft_strncpy(copy, (*line), j);
	free(*line);
	return (copy);
}
