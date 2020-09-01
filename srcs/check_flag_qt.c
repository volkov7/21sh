/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_flag_qt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 18:48:15 by nriker            #+#    #+#             */
/*   Updated: 2020/08/01 19:00:05 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		enter_press_heredok(t_input *i)
{
	if (!i->qt)
	{
		if (!ft_strchr(i->line, '\n'))
			if (i->line[i->x - i->index] != '\n')
				i->line = lineadd(&i->line, '\n', i->width - i->index);
	}
	else if (i->line[i->width - i->index] != '\n')
		i->line = lineadd(&i->line, '\n', i->width - i->index);
}

void		get_command_params_qt(t_input *input, t_input *old_input, int len)
{
	if (input->quote)
		input->width_quote = len + input->index;
	else if (input->dquote)
		input->width_dquote = len + input->index;
	input->width = ft_strlen(input->line) + input->index;
	input->x = input->width;
	input->y = get_curs_row();
	if (input->quote)
	{
		input->x_quote = input->width_quote;
		input->qlines_in_com = old_input->lines_in_com;
		input->lines_in_com = input->lines_in_com + input->qlines_in_com;
	}
	else if (input->dquote)
	{
		input->x_dquote = input->width_dquote;
		input->dqlines_in_com = old_input->lines_in_com;
		input->lines_in_com = input->lines_in_com + input->dqlines_in_com;
	}
}

t_input		*insert_history_line(t_input *input)
{
	char	*str;
	char	*str2;
	char	*str3;
	int		len;
	t_input	*old_input;

	old_input = input;
	str = ft_strcut(input->line, '\n');
	while (input && input->prev)
		input = input->prev;
	str2 = ft_strrchr(input->line, '\n') + 1;
	len = (ft_strlen(input->line) - ft_strlen(str2)) + 1;
	str3 = ft_strnew(len);
	ft_strncpy(str3, input->line, len - 1);
	if (input->quote)
		input->lines_in_com = input->lines_in_com - input->qlines_in_com;
	else if (input->dquote)
		input->lines_in_com = input->lines_in_com - input->dqlines_in_com;
	free(input->line);
	len = ft_strlen(str);
	input->line = ft_strjoinfreefree(str3, str);
	get_command_params_qt(input, old_input, len);
	return (input);
}

int			check_flag_qt(t_input *input)
{
	while (input && input->prev)
		input = input->prev;
	if (input->qt)
		return (1);
	return (0);
}
