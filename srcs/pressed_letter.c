/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pressed_letter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 14:23:06 by nriker            #+#    #+#             */
/*   Updated: 2020/08/08 09:10:04 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		insert_letter_between_q(t_input *input, char buf[7])
{
	ft_putchar(buf[0]);
	ft_putstr(&input->line[input->x - (input->index - 1)]);
	input->row = get_curs_row();
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
	if (!((input->x_quote) % input->col))
		input->y++;
	input->row = get_curs_row();
	ft_printf("\e[%d;%dH", input->y, (input->x_quote % input->col) + 1);
}

void		insert_letter_between_dq(t_input *input, char buf[7])
{
	ft_putchar(buf[0]);
	ft_putstr(&input->line[input->x - (input->index - 1)]);
	input->row = get_curs_row();
	if (!(input->width_dquote % input->col) && input->row == input->li)
	{
		ft_putchar('\n');
		input->lines_in_com++;
		input->dqlines_in_com++;
		input->y--;
	}
	else if (!((input->width_dquote) % input->col))
	{
		input->lines_in_com++;
		input->qlines_in_com++;
	}
	if (!((input->x_dquote) % input->col))
		input->y++;
	input->row = get_curs_row();
	ft_printf("\e[%d;%dH", input->y, (input->x_dquote % input->col) + 1);
}

void		pressed_letter_q(t_input *input, char buf[7])
{
	if (input->x_quote < input->width_quote)
		insert_letter_between_q(input, buf);
	else if (input->x_dquote < input->width_dquote)
		insert_letter_between_dq(input, buf);
	else
		print_letter_q(input, buf);
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

void		insert_letter_between(t_input *input, char buf[7])
{
	ft_putchar(buf[0]);
	insert_print_string(input);
	input->row = get_curs_row();
	if (!(input->width % input->col) && input->row == input->li)
	{
		ft_putchar('\n');
		input->y--;
	}
	else if (!((input->x) % input->col))
		input->y++;
	input->row = get_curs_row();
	ft_printf("\e[%d;%dH", input->y, (input->x % input->col) + 1);
}

void		pressed_letter(t_input *input, char buf[7])
{
	if (input->x < input->width && !input->flag)
		insert_letter_between(input, buf);
	else if (input->x < input->width && input->flag)
		insert_letter_betweenhistory(input, buf);
	else
	{
		ft_putchar(buf[0]);
		if (!((input->x) % input->col))
			ft_putchar('\n');
		else if (input->width == input->col && input->row == input->li)
		{
			ft_putchar('\n');
			input->y--;
		}
	}
}
