/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_insert_word.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 09:34:04 by nriker            #+#    #+#             */
/*   Updated: 2020/05/17 02:59:53 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		curs_endofword(t_input *input)
{
	while (input->line[input->x - input->index] != ' '
		&& input->line[input->x - input->index])
	{
		if (!(input->x & input->col))
			ft_putstr("\e[1E");
		else
			ft_putstr("\e[1C");
		input->x++;
	}
	if (input->x % input->col == 1)
	{
		ft_putstr("\e[1A");
		ft_printf("\e[%dG", input->col);
	}
	else
		ft_putstr("\e[1D");
	input->x--;
}

void		delete_word(t_input *input)
{
	while (input->line[input->x - (input->index + 1)] != ' ' && input->x > input->index
			&& input->x - input->index > input->sx)
	{
		input->line = lineremove(input->line, input->x - input->index);
		if (input->x % input->col == 1)
		{
			ft_putstr("\e[1A");
			ft_printf("\e[%dG", input->col);
		}
		else
			ft_putstr("\e[1D");
		input->x--;
		input->width--;
	}
	input->line = lineremove(input->line, input->x - input->index);
	input->width--;
}

void		tab_insert_word(t_input *input, char **buf)
{
	int x;

	x = 0;
	curs_endofword(input);
	delete_word(input);
	input->c = input->x;
	while (x < ft_strlen(buf[0]))
	{
		input->line = lineadd(&input->line, buf[0][x], input->c - input->index);
		input->width++;
		x++;
		input->c++;
	}
	ft_putchar('\n');
	input->x += ft_strlen(buf[0]);
	print_suggestion(input);
	input->c = input->width;
	input->row = get_curs_row();
}
