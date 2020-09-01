/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 06:55:55 by nriker            #+#    #+#             */
/*   Updated: 2020/08/02 06:55:56 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_init			*get_i(t_init *str)
{
	static t_init	*in;

	if (!str)
		return (in);
	else
		in = str;
	return (0);
}

void			create_init(t_init *in)
{
	if (!(in->terminal = getenv("TERM")))
		ft_error_select(2);
	if ((in->fd = open("/dev/tty", O_RDWR)) == -1)
		ft_error_select(0);
	in->bad_window = 0;
	in->call = 0;
	in->row = 0;
	in->nb = 0;
	in->col = 7;
	get_i(in);
}
