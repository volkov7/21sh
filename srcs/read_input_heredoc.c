/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 12:39:33 by root              #+#    #+#             */
/*   Updated: 2020/05/24 10:53:40 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		set_hdoc(t_input *copy, int x, int index)
{
	while (copy)
	{
		copy->hdoc = x;
		// copy->index = index;
		copy = copy->next;
	}
}

t_input		*fill_param_heredoc(t_input *input, int x)
{
	t_input		*copy;

	input->hdoc = x;
	copy = copyinput(input);
	free(copy->line);
	copy->line = ft_strdup("");
	if (x == 1)
	{
		ft_putstr("> ");
		copy->x = 3;
		copy->width = 3;
		copy->index = 3;
	}
	else if (x == 2)
	{
		ft_putstr("heredoc> ");
		copy->x = 10;
		copy->width = 10;
		copy->index = 10;
	}
	set_hdoc(copy, x, copy->index);
	copy->y = get_curs_col();
	copy->row = copy->y;
	copy->lines_in_com = 1;
	copy->lines_in_qt = 1;
	copy->qlines_in_com = 1;
	copy->dqlines_in_com = 1;
	return (copy);
}

char		*read_input_heredoc(t_init *in, t_input *input, int x)
{
	char		buf[7];
	t_input		*copy;
	char		*str;

	copy = fill_param_heredoc(input, x);
	ft_bzero((void*)buf, 7);
	while (1)
	{
		if (read(0, buf, 7) == -1)
			ft_error();
		// if ((buf[0] == 13 || buf[0] == 10) && !buf[1]
		// 	&& copy->flag && check_flag_qt(copy))
		// 	copy = insert_history_line(copy);
		if (buf[0] == 27 && buf[1] == 91 && (buf[2] == 65 || buf[2] == 66
				|| buf[2] == 67 || buf[2] == 68))
			copy = arrowpress(in, copy, buf);
		else if (!letterpress(in, copy, buf) || !delete_press(in, copy, buf)
			|| !specialpress(in, copy, buf) || !enter_press(in, copy, buf))
		{
			input->line = ft_strjoinfree(input->line, copy->line);
			str = ft_strdup(copy->line);
			free_input(copy);
			return (str);
		}
		ft_bzero((void*)buf, 7);
	}
	return (copy->line);
}
