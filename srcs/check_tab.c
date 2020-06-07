/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 11:14:38 by nriker            #+#    #+#             */
/*   Updated: 2020/05/17 02:44:40 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// int			check_startline(t_input *input)
// {
// 	int		len;
// 	int		i;
// 	int		col;

// 	len = 0;
// 	i = 0;
// 	while (input->line[i])
// 	{
// 		if (input->line[i] == '\t')
// 			len += 8;
// 		else
// 			len++;
// 		i++;
// 	}
// 	col = tgetnum("co");
// 	ft_printf("%d", col);
// 	return (0);
// }

// char		*get_firstword(t_input *input)
// {
// 	char	*line;
// 	int		x;

// 	if (line[x] != ' ' || (line[x - 1] != ' '))
// 	{
// 		while (line[x - 1] != '\t' && line[x - 1] != ' ')
// 			x--;
// 		input->sx = x;
// 		while (line[x] != '\t' && line[x] != ' ' && line[x])
// 			x++;
// 		input->sy = x;
// 	}
// 	line = ft_strnew(input->sy - input->sx);
// 	line = ft_strncpy(line, input->line + input->sx, input->sy - input->sx);
// 	return (line);
// }

int			check_point_slesh(t_input * input, char *line, int x)
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

	if (input->qt)
		return (get_partword_q(input));
	else
	{
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
		// 	ft_printf("!%s! %d!", line, input->x - 8);
		// while (1);
			return (line);
		}
		return (0);
	}
}

int			check_firstword(t_input *input)
{
	int		i;

	if (input->qt)
		return (check_firstword_q(input));
	else
	{
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
}
// int			check_partword(t_input *input)
// {
// 	int		x;
// 	char	*line;

// 	line = input->line;
// 	x = input->x - 8;
// 	// ft_putchar(input->line[x]);
// 	if (line[x] == ' ' && line[x - 1] == ' ' && line[x + 1] != ' ' && line[x + 1])
// 		return (1);
// 	else if ((((line[x] == '\t' && line[x + 1] == '\t') || !line[x])
// 		&& line[x - 1] == '\t') || (((line[x] == ' ' && line[x +  1] == ' ')
// 		|| !line[x]) && line[x - 1] == ' '))
// 		return (1);
// 	return (0);
// }


// int			check_qfirstword(t_input *input, int x)
// {
// 	int		i;

// 	if (input->quote)
// 	{
// 		x -= 7;
// 		i = input->width - input->width_quote;
// 	}
// 	else if (input->dquote)
// 	{
// 		x -= 8;
// 		i = input->width - input->width_dquote + 1;
// 	}
// 	// ft_printf(" %d %d", input->width_dquote, i);
// 	// ft_printf(" %d %d", x, i);
// 	// if (input->line[i] == '\t')
// 	// 		ft_printf("s%cs", input->line[i]);
// 	if (!ft_strlen(input->line))
// 		return (0);
// 	while (i < x)
// 	{
// 		if (input->line[i] != '\t' && input->line[i] != ' ' && i == x)
// 			return (0);
// 		if (input->line[i] != '\t' && input->line[i] != ' ' && i != x)
// 			return (1);
// 		i++;
// 	}
// 	return (0);
// }

// int			get_firstword(t_input *input)
// {
// 	int		i;

// 	if (!ft_strlen(input->line))
// 		return (0);
// 	i = 0;
// 	while ((input->line[i] == ' ' || input->line[i] == '\t') && input->line[i])
// 		i++;
// 	if (!input->line[i])
// 		return (0);
// 	while (input->line[i] != ' ' && input->line[i] != '\t' && input->line[i])
// 		i++;
// 	return (i);
// }

// int			check_tabparse(t_input *input, int x, int z)
// {
// 	int		i;

// 	x -= z;
// 	i = 0;
// 	if (input->line[x - 1] != ' ')
// 		return (0);
// 	return (1);
// }
