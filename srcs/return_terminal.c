/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_terminal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 10:44:53 by nriker            #+#    #+#             */
/*   Updated: 2020/02/14 18:25:07 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		return_terminal(t_init *in)
{
	// char	*ve;
	// char	*clear;

	if (tcsetattr(0, TCSANOW, &in->old_tr) == -1)
		ft_error();
	// tputs(tgetstr("ei", NULL), in->fd, &putchar_select);
	// tputs(tgetstr("ed", NULL), in->fd, &putchar_select);
	// if (in->story)
	// 	free_story(in->story);
	// if (in->copys)
	// 	free_story(in->copys);
	// ve = tgetstr("ve", 0);
	// clear = tgetstr("cl", 0);
	// tputs(ve, in->fd, &putchar_select);
	// tputs(clear, in->fd, &putchar_select);
	// ft_putstr_fd("\033[?1049l", in->fd);
}
