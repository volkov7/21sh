/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_input_heredoc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 21:49:00 by nriker            #+#    #+#             */
/*   Updated: 2020/08/05 20:22:52 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		set_hdoc(t_input *copy, int x)
{
	while (copy)
	{
		copy->hdoc = x;
		copy = copy->next;
	}
}

void		fill_param_heredoc_2(t_input *copy, int x)
{
	if (x == 1)
	{
		ft_putstr("> ");
		copy->x = 3;
		copy->width = 3;
		copy->index = 3;
		copy->small_heredok = 1;
	}
	else if (x == 2)
	{
		ft_putstr("heredoc> ");
		copy->x = 10;
		copy->width = 10;
		copy->index = 10;
		copy->big_heredok = 1;
	}
}

t_input		*fill_param_heredoc(t_input *input, int x)
{
	t_input		*copy;

	copy = copyinput(input);
	free(copy->line);
	copy->line = ft_strdup("");
	copy->input_original = input;
	copy->heredok = 1;
	fill_param_heredoc_2(copy, x);
	set_hdoc(copy, x);
	copy->y = get_curs_col();
	copy->row = copy->y;
	copy->lines_in_com = 1;
	copy->lines_in_qt = 1;
	copy->qlines_in_com = 1;
	copy->dqlines_in_com = 1;
	return (copy);
}

void		read_input_heredoc_return_command(t_input *copy, int ds)
{
	write(ds, copy->line, ft_strlen(copy->line) - 1);
	free_input(copy);
	close(ds);
	exit(0);
}

void		read_input_heredoc(t_init *in, t_input *input, int x, int ds)
{
	char		buf[7];
	t_input		*copy;

	input->heredok = 1;
	copy = fill_param_heredoc(input, x);
	ft_bzero((void*)buf, 7);
	while (1)
	{
		if (read(0, buf, 7) == -1)
			ft_error();
		get_input(copy);
		if (buf[0] == 27 && buf[1] == 91 && (buf[2] == 65 || buf[2] == 66
				|| buf[2] == 67 || buf[2] == 68))
			copy = arrowpress(copy, buf);
		else if (!letterpress(in, copy, buf) || !delete_press(copy, buf)
			|| !specialpress(copy, buf) || !enter_press(copy, buf))
			read_input_heredoc_return_command(copy, ds);
		ft_bzero((void*)buf, 7);
	}
	exit(0);
}
