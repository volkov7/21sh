/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pressed_letter_q_history.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 06:47:16 by nriker            #+#    #+#             */
/*   Updated: 2020/08/05 21:01:42 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void			print_letter_history(t_input *input, char buf[7])
{
	ft_putchar(buf[0]);
	if (!(input->x_quote % input->col))
	{
		ft_putchar('\n');
		input->lines_in_com++;
		input->qlines_in_com++;
	}
	input->y = get_curs_row();
	input->row = input->y;
}

int				get_width_quote_history(t_input *input)
{
	int		x;
	int		final;
	int		count;

	x = input->x;
	count = 0;
	final = 0;
	x = input->x;
	if (input->quote)
		final = 8;
	else if (input->dquote)
		final = 9;
	while (x >= final && input->line[x - input->index] != '\n')
		x--;
	x++;
	while (input->line[x - input->index] != '\n' && x <= input->width)
	{
		count++;
		x++;
	}
	return (count);
}

void			insert_letter_between_history(t_input *input, char buf[7])
{
	ft_putchar(buf[0]);
	print_history(input, input->line + input->x - input->index + 1, 0);
	input->row = get_curs_row();
	input->width_quote = get_width_quote_history(input);
	if (!(input->width_quote % input->col) && input->row == input->li)
	{
		ft_putchar('\n');
		input->lines_in_com++;
		input->qlines_in_com++;
		input->y--;
	}
	else if (!((input->width_quote) % input->col))
	{
		input->lines_in_com++;
		input->qlines_in_com++;
	}
	if (input->x_quote == input->col)
	{
		input->x_quote = 0;
		input->y++;
	}
	input->row = get_curs_row();
	ft_printf("\e[%d;%dH", input->y, input->x_quote + 1);
}

void			pressed_letter_q_history(t_input *input, char buf[7])
{
	input->y = get_curs_row();
	input->x_quote = get_curs_col();
	if (input->x < input->width)
		insert_letter_between_history(input, buf);
	else
		print_letter_history(input, buf);
	if (input->quote)
	{
		input->width_quote++;
		input->x_quote++;
	}
	else if (input->dquote)
	{
		input->width_dquote++;
		input->x_dquote++;
	}
}
