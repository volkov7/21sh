/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:15:00 by nriker            #+#    #+#             */
/*   Updated: 2020/08/05 20:06:51 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"
#include "lexer.h"

void		sig_exit(int x)
{
	t_init	*in;
	t_input *input;

	in = get_i(0);
	input = get_input(0);
	if (x == 2)
	{
		handle_exit_status(128 + SIGINT);
		return_cursor_when_ctrl_c(input);
	}
	else if (x == 28)
		change_size_of_window(input);
	else if (x != 17 && x != 20 && x != 18)
	{
		return_terminal(in);
		close(in->fd);
		exit(EXIT_SUCCESS);
	}
}

void		signals(void)
{
	int		i;

	i = 0;
	while (++i < 100)
		signal(i, &sig_exit);
}
