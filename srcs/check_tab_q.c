/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tab_q.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 03:10:37 by nriker            #+#    #+#             */
/*   Updated: 2020/05/17 02:44:53 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

char		*get_partword_q(t_input *input)
{
	char	*line;
	int		x;

	if (input->quote)
		line = input->line + (input->width - input->width_quote);
    else if (input->dquote)
		line = input->line + (input->width - input->width_dquote + 1);
	if (input->quote)
		input->c = input->width - input->width_quote;
    else if (input->dquote)
		input->c = input->width - input->width_dquote + 1;////!!!
	x = input->x - 8 - input->c;
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
		line = ft_strncpy(line, (input->line + input->c) + input->sx, input->sy - input->sx);
		// ft_printf("!%s! %d!", line, input->c);
		// while (1);
		return (line);
	}
	return (0);
}

int			check_firstword_q(t_input *input)
{
	int		i;
	int		x;
	char	*line;

	i = 0;
	x = 0;
	if (input->quote)
		line = input->line + (input->width - input->width_quote);
	else if (input->dquote)
		line = input->line + (input->width - input->width_dquote + 1);
	if (input->quote)
		input->c = input->width - input->width_quote;
    else if (input->dquote)
		input->c = input->width - input->width_dquote;
	x = input->x - input->index - input->c;
	if (!ft_strlen(line))
		return (1);
	while ((line[i] == ' ' || line[i] == '\t') && line[i])
		i++;
	while (i < x)
	{
		if ((line[i] == '\t' || line[i] == ' ')
			&& i == x)
			return (1);
		else if ((line[i] == '\t' || line[i] == ' '))
			return (0);
		i++;
	}
	return (1);
}
