/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_tab_output.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 10:52:14 by nriker            #+#    #+#             */
/*   Updated: 2020/02/11 16:49:51 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		clear_tab_output(t_init *in, t_input *input)
{
	int		col;

	if (!input->tab_row)
		return ;
	col = input->x % tgetnum("co");
	while (col--)
		tputs(tgetstr("le", NULL), in->fd, &putchar_select);
	tputs(tgetstr("do", 0), in->fd, &putchar_select);
	// tputs(tgoto("DL", 150, 10), in->fd, &putchar_select);
	col = input->tab_row + 1;
	while (col--)
	{
		tputs(tgetstr("ce", NULL), in->fd, &putchar_select);
		tputs(tgetstr("do", 0), in->fd, &putchar_select);
	}
	while (col++ < input->tab_row + 1)
		tputs(tgetstr("up", 0), in->fd, &putchar_select);
	col = 0;
	while (col != input->x % tgetnum("co"))
	{
		tputs(tgetstr("nd", NULL), in->fd, &putchar_select);
		col++;
	}
}
