/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 11:14:38 by nriker            #+#    #+#             */
/*   Updated: 2020/08/02 06:37:09 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			check_point_slesh(t_input *input, char *line, int x)
{
	int k;

	k = x;
	if (line[k] == '.')
	{
		k++;
		if (line[k] == '.')
			k++;
		if (line[k] != '/')
			return (x);
		while (line[k] == '/' && line[k])
			k++;
		input->exec_firstword = 1;
		return (k);
	}
	return (x);
}

char		*get_partword(t_input *input)
{
	char	*line;
	int		x;

	line = input->line;
	x = input->x - input->index;
	if (!ft_strlen(line) || (!x && line[x] == ' '))
		return (0);
	if (line[x] != ' ' || (line[x - 1] != ' '))
	{
		while (x > 0 && line[x - 1] != '\t' && line[x - 1] != ' ')
			x--;
		x = check_point_slesh(input, line, x);
		input->sx = x;
		while (line[x] != '\t' && line[x] != ' ' && line[x])
			x++;
		input->sy = x;
		line = ft_strnew(input->sy - input->sx);
		line = ft_strncpy(line, input->line + input->sx, input->sy - input->sx);
		return (line);
	}
	return (0);
}

int			check_firstword(t_input *input)
{
	int		i;

	i = 0;
	if (!ft_strlen(input->line))
		return (1);
	while (input->line[i] == ' ' || input->line[i] == '\t')
		i++;
	while (i + input->index < input->x)
	{
		if ((input->line[i] == '\t' || input->line[i] == ' ')
			&& i == input->x - input->index)
			return (1);
		else if ((input->line[i] == '\t' || input->line[i] == ' '))
			return (0);
		i++;
	}
	return (1);
}
