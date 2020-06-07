/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specialpress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 08:02:57 by root              #+#    #+#             */
/*   Updated: 2020/05/24 12:56:36 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		set_cursor_in_home(int len, t_input *input)
{
	int x;

	x = get_curs_col();
	while (len--)
	{
		if ((x % input->col) == 1)
		{
			ft_putstr("\e[1A");
			ft_printf("\e[%dG", input->col);
			input->y--;
			x = input->col;
		}
		else
		{
			ft_putstr("\e[1D");
			x--;
		}
		if (input->quote)
			input->x_quote--;
		else if (input->dquote)
			input->x_dquote--;
		input->x--;
	}
}

void		set_cursor_in_end(int len, int width, t_input *input)
{
	int	x;

	x = get_curs_col();
	while (len < width)
	{
		if (!(x % input->col))
		{
			ft_putstr("\e[1E");
			input->y++;
			x = 0;
		}
		else
			ft_putstr("\e[1C");
		x++;
		len++;
		if (input->quote)
			input->x_quote++;
		else if (input->dquote)
			input->x_dquote++;
		input->x++;
	}
}

void		set_cursor_prev_1(int *x, t_input *input)
{
	int		xt;

	xt = get_curs_col();
	while ((*x) && input->line[*x] == ' ')
	{
		if ((xt % input->col) == 1)
		{
			ft_putstr("\e[1A");
			ft_printf("\e[%dG", input->col);
			input->y--;
			xt = input->col;
		}
		else
		{
			ft_putstr("\e[1D");
			xt--;
		}
		if (input->quote)
			input->x_quote--;
		else if (input->dquote)
			input->x_dquote--;
		input->x--;
		(*x)--;
	}
}

void		set_cursor_prev_2(int *x, t_input *input)
{
	int		xt;

	xt = get_curs_col();
	while ((*x) && input->line[*x] != ' ')
	{
		if ((xt % input->col) == 1)
		{
			ft_putstr("\e[1A");
			ft_printf("\e[%dG", input->col);
			input->y--;
			xt = input->col;
		}
		else
		{
			ft_putstr("\e[1D");
			xt--;
		}
		if (input->quote)
			input->x_quote--;
		else if (input->dquote)
			input->x_dquote--;
		input->x--;
		(*x)--;
	}
}

void		set_cursor_second_1(int *x, int width, t_input *input)
{
	int	xt;

	xt = get_curs_col();
	while (((*x) < width) && input->line[*x] == ' ')
	{
		if (!(xt % input->col))
		{
			ft_putstr("\e[1E");
			input->y++;
			xt = 0;
		}
		else
			ft_putstr("\e[1C");
		xt++;
		(*x)++;
		if (input->quote)
			input->x_quote++;
		else if (input->dquote)
			input->x_dquote++;
		input->x++;
	}
}

void		set_cursor_second_2(int *x, int width, t_input *input)
{
	int	xt;

	xt = get_curs_col();
	while (((*x) < width) && input->line[*x] != ' ')
	{
		if (!(xt % input->col))
		{
			ft_putstr("\e[1E");
			input->y++;
			xt = 0;
		}
		else
			ft_putstr("\e[1C");
		xt++;
		(*x)++;
		if (input->quote)
			input->x_quote++;
		else if (input->dquote)
			input->x_dquote++;
		input->x++;
	}
}

void		set_cursor_prev_word(int x, t_input *input)
{
	if (x == ft_strlen(input->line))
		x--;
	if (input->line[x] == ' ')
	{
		set_cursor_prev_1(&x, input);
	}
	else if (input->line[x] != ' ')
	{
		set_cursor_prev_2(&x, input);
		set_cursor_prev_1(&x, input);
	}
}

void		set_cursor_second_word(int x, int width, t_input *input)
{
	if (input->line[x] == ' ')
	{
		set_cursor_second_1(&x, width, input);
	}
	else if (input->line[x] != ' ')
	{
		set_cursor_second_2(&x, width, input);
		set_cursor_second_1(&x, width, input);
	}
}

void		pressed_home(t_input *input)
{
	if (!input->qt)
		set_cursor_in_home(input->x - input->index, input);
	else if (input->quote)
		set_cursor_in_home(input->x_quote - 8, input);
	else if (input->dquote)
		set_cursor_in_home(input->x_dquote - 9, input);
}

void		pressed_end(t_input *input)
{
	if (!input->qt)
		set_cursor_in_end(input->x, input->width, input);
	else if (input->quote)
		set_cursor_in_end(input->x_quote, input->width_quote, input);
	else if (input->dquote)
		set_cursor_in_end(input->x_dquote, input->width_dquote, input);
}

void		pressed_prev_word(t_input *input)
{
	if (!input->qt)
		set_cursor_prev_word(input->x - input->index, input);
	else if (input->quote)
		set_cursor_prev_word(input->x_quote - 8, input);
	else if (input->dquote)
		set_cursor_prev_word(input->x_dquote - 9, input);
}

void		pressed_second_word(t_input *input)
{
	int		width;

	width = input->width - input->index;
	set_cursor_second_word(input->x - input->index, width, input);
}

void		pressed_copy(t_input *input)
{
	
}

int			specialpress(t_init *in, t_input *input, char buf[7])
{
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 72 && !buf[3])
		pressed_home(input);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 70 && !buf[3])
		pressed_end(input);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 54 && buf[3] == 126)
		pressed_prev_word(input);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 53 && buf[3] == 126)
		pressed_second_word(input);
	else if (buf[0] == 1 && !buf[1] && !buf[2] && !buf[3])
		pressed_copy(input);
	
	return (1);
}
