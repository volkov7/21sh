/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pressed_letter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/17 14:23:06 by nriker            #+#    #+#             */
/*   Updated: 2020/05/24 10:13:25 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		insert_print_string(t_input *input)
{
	char	*str;
	int		len;

	if (input->flag)
	{
		len = ft_strlen(&input->line[input->x - (input->index - 1)] + 1);
		str = ft_strnew(len);
		ft_putstr(ft_strncpy(str, &input->line[input->x - input->index] + 1, len));
		// ft_putstr(ft_strncpy(str, &input->line[input->x - 7], ft_strlen(len)));
		free(str);
	}
	else
		ft_putstr(&input->line[input->x - (input->index - 1)]);
}


void		insert_letter_between_q(t_init *in, t_input *input, char buf[7])
{
	int		x;
	int		y;

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
		// ft_putchar('\n');//////!!!!!!!!!!
		// ft_putchar('\n');//////!!!!!!!!!!
		input->lines_in_com++;
		input->qlines_in_com++;
		// input->y++;
	}
	if (!((input->x_quote) % input->col))
	{
		// ft_putchar('\n');
		// if (input->row != input->li)
			input->y++;
	}
	input->row = get_curs_row();
	ft_printf("\e[%d;%dH", input->y, (input->x_quote % input->col) + 1);
}

void		insert_letter_between_dq(t_init *in, t_input *input, char buf[7])
{
	int		x;
	int		y;

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
		// input->y++;
	}
	if (!((input->x_dquote) % input->col))
	{
		// ft_putchar('\n');
		// if (input->row != input->li)
			input->y++;
	}
	input->row = get_curs_row();
	ft_printf("\e[%d;%dH", input->y, (input->x_dquote % input->col) + 1);
}

void		print_letter_q(t_init *in, t_input *input, char buf[7])
{
	ft_putchar(buf[0]);
	if (input->quote)
	{
		if (!(input->x_quote % input->col))
		{
			ft_putchar('\n');
			input->lines_in_com++;
			input->qlines_in_com++;
		}
	}
	else if (input->dquote)
	{
		if (!((input->x_dquote) % input->col))
		{
			ft_putchar('\n');
			input->lines_in_com++;
			input->dqlines_in_com++;
		}
	}
	input->y = get_curs_row(); /////!!!
	input->row = input->y; ////!!!!
}

void		pressed_letter_q(t_init *in, t_input *input, char buf[7])
{
	if (input->x_quote < input->width_quote)
		insert_letter_between_q(in, input, buf);
	else if (input->x_dquote < input->width_dquote)
		insert_letter_between_dq(in, input, buf);
	else
		print_letter_q(in, input, buf);
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

void		insert_letter_between(t_init *in, t_input *input, char buf[7])
{
	int		x;
	int		y;

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

void		pressed_letter(t_init *in, t_input *input, char buf[7])
{
	if (input->x < input->width)
		insert_letter_between(in, input, buf);
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
