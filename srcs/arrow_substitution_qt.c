/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_substitution_qt.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 15:19:08 by nriker            #+#    #+#             */
/*   Updated: 2020/07/04 14:04:32 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			get_len_next_line_qt(t_input *input)
{
	int len;

	len = 0;
	input->x_quote = get_curs_col();
	input->c = input->x;
	while (input->line[input->c - (input->index + 1)] != '\n' && input->c > input->index)
	{
		if (input->x_quote % input->col == 1)
			input->x_quote = input->col;
		else
			input->x_quote--;
		input->c--;
		len++;
	}
	return (len);
}

void		set_cursor_next_line(t_input *input)
{
	// input->c = get_curs_col();
	while ((input->x - (input->index + 1))
		&& input->line[input->x - (input->index + 1)] != '\n')
	{
		if (input->x_quote % input->col == 1)
		{
			ft_putstr("\e[1A");
			ft_printf("\e[%dG", input->col);
			input->x_quote = input->col;
			input->y--;
			// input->x--;
		}
		else
		{
			// ft_putchar('W');
			ft_putstr("\e[1D");
			// ft_putstr("\e[1D");
			input->x_quote--;
		}
		input->x--;
	}
	// while (1);
	// while (1);
	// if (input->dflag != 2)
	// {
		// input->x++;

	input->dflag--;
	// ft_putchar('W');
	input->x_quote = sub_get_x(input, 3);
	ft_putstr("\e[1A");
	ft_printf("\e[%dG", input->x_quote % input->col);
	// ft_printf("%d", input->x_quote);
	input->y--;
	input->x--;
	input->c = get_len_next_line_qt(input);
	// ft_printf("%d", input->len_qt);
	input->x_quote = get_curs_col();
	// input->y = get_curs_row();
	if (input->c <= input->len_qt)
		return ;
	input->c -= input->len_qt;
	while (input->c > 0 && input->x > input->index)
	{
		if (input->x_quote % input->col == 1)
		{
			ft_putstr("\e[1A");
			ft_printf("\e[%dG", input->col);
			input->x_quote = input->col;
			input->y--;
			// input->x--;
		}
		else
		{
			// ft_putchar('W');
			ft_putstr("\e[1D");
			input->x_quote--;
		}
		input->c--;
		input->x--;
		// len++;
	}
	input->c = input->len_qt;
	input->x_quote = get_curs_col();
}

void		set_cursor_prev_line(t_input *input)
{
	while (input->line[input->x - input->index] != '\n')
	{
		if (!(input->x_quote % input->col))
		{
			ft_putstr("\e[1E");
			input->x_quote = 1;
			input->y++;
		}
		else
		{
			ft_putstr("\e[1C");
			input->x_quote++;
		}
		input->x++;
	}
	ft_putstr("\e[1E");
	input->x_quote = 1;
	input->dflag++;
	input->y++;
	input->x++;
	input->c = input->len_qt;
	input->x_quote = get_curs_col();
	// input->y = get_curs_row();
	if (input->line[input->x - input->index] == '\n')
		return ;
	// ft_printf("%d %d", input->x, input->width);
	while (input->c > 0 && input->x <= input->width)
	{
		if (input->line[input->x - input->index] == '\n')
			break ;
		else if (!(input->x_quote % input->col) && input->line[input->x - (input->index + 1)] != '\n')
		{
			ft_putstr("\e[1E");
			input->y++;
			input->x_quote = 1;
		}
		else if (input->x < input->width)
		{
			ft_putstr("\e[1C");
			input->x_quote++;
		}
		input->c--;
		input->x++;
	}
	// ft_putchar('Q');
	// ft_printf("%d %d", input->x, input->width);
	if (input->x > input->width)
		input->x = input->width;
	// ft_printf("%d %d", input->x, input->width);
	input->x_quote = get_curs_col();
	// input->y = get_curs_row();
}

int			get_len_of_line(t_input *input)
{
	int len;

	len = 0;
	input->c = input->x;
	if (input->line[input->c - input->index] == '\n')
	{
		len++;
		input->c--;
	}
	while (input->line[input->c - (input->index + 1)] != '\n' && input->c != input->index)
	{
		len++;
		input->c--;
	}
	return (len);
}

void		up_sub_qt(t_input *input)
{
	input->x_quote = get_curs_col();


	// input->sx = input->x;
	// ft_putchar('Q');
	if (!input->flag_qt)
	{
		// ft_putchar('Q');
		input->len_qt = get_len_of_line(input);
		// ft_printf("%d", input->len_qt);
		// ft_printf("%d %d", input->len_qt, input->col);
	}
	input->flag_qt = 1;
	// ft_printf("%d", input->len_qt);
	// ft_printf("!!%d %d!", input->sx, input->x);
	set_cursor_next_line(input);
}

void		down_sub_qt(t_input *input)
{
	input->x_quote = get_curs_col();
	if (!input->flag_qt)
	{
		input->len_qt = get_len_of_line(input);
		// ft_printf("%d", input->len_qt);
	}
	// ft_printf("%d", input->len_qt);
	input->flag_qt = 1;
	set_cursor_prev_line(input);
	// set_cursor_prev_line();
}
