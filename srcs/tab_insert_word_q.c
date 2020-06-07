/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_insert_word_q.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 14:10:08 by nriker            #+#    #+#             */
/*   Updated: 2020/05/17 02:33:03 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		curs_endofword_dq(t_input *input)
{
	while (input->line[input->x - 8] != ' '
		&& input->line[input->x - 8])
	{
		if (!(input->x_dquote & input->col))
			ft_putstr("\e[1E");
		else
			ft_putstr("\e[1C");
		input->x_dquote++;
        input->x++;
	}
	if (input->x_dquote % input->col == 1)
	{
		ft_putstr("\e[1A");
		ft_printf("\e[%dG", input->col);
	}
	else
		ft_putstr("\e[1D");
	input->x--;
    input->x_dquote--;
}

void		curs_endofword_q(t_input *input)
{
	if (input->dquote)
		curs_endofword_dq(input);
	else
	{
		while (input->line[input->x - 8] != ' '
			&& input->line[input->x - 8])
		{
			if (!(input->x_quote & input->col))
				ft_putstr("\e[1E");
			else
				ft_putstr("\e[1C");
			input->x_quote++;
			input->x++;
		}
		if (input->x_quote % input->col == 1)
		{
			ft_putstr("\e[1A");
			ft_printf("\e[%dG", input->col);
		}
		else
			ft_putstr("\e[1D");
		input->x--;
		input->x_quote--;
	}
}

void		delete_word_dq(t_input *input)
{
	while (input->line[input->x - 9] != ' ' && input->x_dquote > 9
			&& input->x_dquote - 8 > input->sx + 1)
	{
		input->line = lineremove(input->line, input->x - input->index);
		if (input->x_dquote % input->col == 1)
		{
			ft_putstr("\e[1A");
			ft_printf("\e[%dG", input->col);
		}
		else
			ft_putstr("\e[1D");
		input->x_dquote--;
		input->width_dquote--;
		input->x--;
		input->width--;
	}
	input->line = lineremove(input->line, input->x - input->index);
	input->width--;
	input->width_dquote--;
}

void		delete_word_q(t_input *input)
{
	if (input->dquote)
		delete_word_dq(input);
	else
	{
		while (input->line[input->x - 9] != ' ' && input->x_quote > 8
				&& input->x_quote - 8 > input->sx)
		{
			input->line = lineremove(input->line, input->x - input->index);
			if (input->x_quote % input->col == 1)
			{
				ft_putstr("\e[1A");
				ft_printf("\e[%dG", input->col);
			}
			else
				ft_putstr("\e[1D");
			input->x_quote--;
			input->width_quote--;
			input->x--;
			input->width--;
		}
		input->line = lineremove(input->line, input->x - input->index);
		input->width--;
		input->width_quote--;
	}
}

void		tab_insert_word_q(t_input *input, char **buf)
{
    int x;

	x = 0;
	curs_endofword_q(input);
	delete_word_q(input);
	input->c = input->x;
	while (x < ft_strlen(buf[0]))
	{
		input->line = lineadd(&input->line, buf[0][x], input->c - input->index);
		input->width++;
		x++;
		input->c++;
	}
	ft_putchar('\n');
	if (input->quote)
		input->x_quote += ft_strlen(buf[0]);
	else if (input->dquote)
		input->x_dquote += ft_strlen(buf[0]);
	if (input->quote)
		input->width_quote += ft_strlen(buf[0]);
	else if (input->dquote)
		input->width_dquote += ft_strlen(buf[0]);
	input->x += ft_strlen(buf[0]);
	print_suggestion(input);
	input->row = get_curs_row();
}
