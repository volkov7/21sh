/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrowpress.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 11:59:34 by nriker            #+#    #+#             */
/*   Updated: 2020/05/17 07:07:36 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		standart_left(t_init *in, t_input *input, char buf[7], int start)
{
	if ((!input->qt
		&& input->x % input->col == 1)
		|| (input->x_quote % input->col == 1)
		|| (input->x_dquote % input->col == 1))
	{
		// ft_putstr("S");
		ft_putstr("\e[1A");
		ft_printf("\e[%dG", input->col);
		input->y--;
	}
	else
		ft_putstr("\e[1D");
	input->x--;
	// if (input->hdoc)
	// 	input->x_hdoc--;
	// ft_putchar('W');
}

void		history_left(t_init *in, t_input *input, char buf[7], int start)
{
	input->flag_qt = 0;
	if (input->qt && input->line[input->x - (input->index + 1)] == '\n')
	{
		input->dflag--;
		input->x_quote = sub_get_x(input, 3);
		ft_putstr("\e[1A");
		ft_printf("\e[%dG", input->x_quote);
		input->y--;
	}
	else if (input->x_quote % input->col == 1)
	{
		ft_putstr("\e[1A");
		ft_printf("\e[%dG", input->col);
		input->x_quote = input->col;
		input->y--;
	}
	else
	{
		ft_putstr("\e[1D");
		input->x_quote--;
	}
	input->x--;
}

void		arrowpress_left(t_init *in, t_input *input, char buf[7], int start)
{
	if ((input->flag && input->qt && input->x > start))
		history_left(in, input, buf, start);
	else if ((((input->x > start && !input->qt) || input->x_quote > start
			|| input->x_dquote > start) && !input->flag)
			|| (input->flag && !input->qt && input->x > start)
			/*|| (input->hdoc && input->x_hdoc > start)*/)
		standart_left(in, input, buf, start);
	if (input->x_quote > start && !input->flag)
		input->x_quote--;
	else if (input->x_dquote > start && !input->flag)
		input->x_dquote--;
}

void		press_left(t_init *in, t_input *input, char buf[7])
{
	int		start;

	input->p_tab = 0;
	input->p_tab_part = 0;
	if (input->hdoc == 1)
		start = 3;
	else if (input->hdoc == 2)
		start = 10;
	else if (!input->qt)
		start = 8;
	else if (input->qt)
		start = 8;
	// else if (!input->hdoc && !input->dquote)
	// 	start = 8;
	// ft_printf("%d", start);
	// while (1);
	arrowpress_left(in, input, buf, start);
}

void		standart_right(t_init *in, t_input *input, char buf[7])
{
	if ((!input->qt && !(input->x % input->col))
		|| (input->quote && !(input->x_quote % input->col))
		|| (input->dquote && !(input->x_dquote % input->col)))
	{
		ft_putstr("\e[1E");
		input->y++;
	}
	else
		ft_putstr("\e[1C");
	// if (input->hdoc)
	// 	input->x_hdoc++;
	input->x++;
}

void		history_right(t_init *in, t_input *input, char buf[7])
{
	input->flag_qt = 0;
	if (input->line[input->x - 8] == '\n')
	{
		ft_putstr("\e[1E");
		input->x_quote = 1;
		input->dflag++;
		input->y++;
	}
	else if (!(input->x_quote % input->col))
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

void		arrowpress_right(t_init *in, t_input *input, char buf[7])
{
	
	if (input->flag && input->qt && input->x < input->width)
		history_right(in, input, buf);
	else if (((!input->qt && input->x < input->width))
		|| (!input->flag
			&& input->quote && input->x_quote < input->width_quote)
		|| (!input->flag
			&& input->x_dquote && input->x_dquote < input->width_dquote)
		|| (input->flag && !input->qt && input->x < input->width))
		standart_right(in, input, buf);
	if (input->quote && input->x_quote < input->width_quote
		&& !input->flag)
		input->x_quote++;
	else if (input->x_dquote && input->x_dquote < input->width_dquote
		&& !input->flag)
		input->x_dquote++;
}

void		press_right(t_init *in, t_input *input, char buf[7])
{
	input->p_tab = 0;
	input->p_tab_part = 0;
	arrowpress_right(in, input, buf);
}

t_input		*arrowpress(t_init *in, t_input *input, char buf[7])
{
	/*
	** Pressed LEFT
	*/
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68)
		press_left(in, input, buf);
	/*
	** Pressed RIGHT
	*/
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67)
		press_right(in, input, buf);
	/*
	** Pressed UP
	*/
    else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
		return (up_sub(in, input, buf));
	/*
	** Pressed DOWN
	*/
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
		return (down_sub(in, input, buf));
	return (input);
}
