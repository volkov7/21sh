/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letterpress.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 14:07:13 by nriker            #+#    #+#             */
/*   Updated: 2020/08/05 20:45:25 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"
#include "lexer.h"

int			pressed_ctrl_d_not_heredok_exit_qt(t_input *input)
{
	ft_putchar('\n');
	ft_putstr(input->line);
	create_input_ctrl_c(input);
	input = get_input(0);
	input->pressed_ctrl_d = 1;
	return (0);
}

void		pressed_ctrl_d_not_heredok_exit(t_init *in, t_input *input)
{
	ft_putstr("\nexit\n");
	return_terminal(in);
	close(in->fd);
	free_input(input);
	exit(EXIT_SUCCESS);
}

int			pressed_ctrl_d_not_heredok(t_init *in, t_input *input)
{
	if (!input->qt)
	{
		if (input->width == 8)
			pressed_ctrl_d_not_heredok_exit(in, input);
		else if (input->width != 8)
			return (1);
	}
	else if (!input->flag && ((input->quote && input->width_quote == 8)
		|| (input->dquote && input->width_dquote == 9)))
		return (pressed_ctrl_d_not_heredok_exit_qt(input));
	else
		return (1);
	return (0);
}

int			pressed_ctrl_d(t_init *in, t_input *input)
{
	if (!input->heredok)
		return (pressed_ctrl_d_not_heredok(in, input));
	else
		return (pressed_ctrl_d_heredok(input));
	return (0);
}

int			letterpress(t_init *in, t_input *input, char buf[7])
{
	if (buf[0] == 4 && !buf[1] && !buf[2] && !buf[3])
		return (pressed_ctrl_d(in, input));
	else if (!check_letter(buf))
	{
		input->line = lineadd(&input->line, buf[0], input->x - input->index);
		if (!((input->width) % input->col) && !input->qt)
			input->lines_in_com++;
		if ((!((input->width) % input->col)) && !input->qt)
			if (input->row < input->li)
				input->row++;
		if (input->flag)
			input->flag_qt = 0;
		if (!input->qt)
			pressed_letter(input, buf);
		else if (!input->flag)
			pressed_letter_q(input, buf);
		else
			pressed_letter_q_history(input, buf);
		input->y = get_curs_row();
		input->width++;
		input->x++;
	}
	return (1);
}
