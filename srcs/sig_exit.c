/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 11:15:00 by nriker            #+#    #+#             */
/*   Updated: 2020/02/06 16:33:56 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// void		sigint(void)
// {
// 	int		fd;
// 	char	*ve;
// 	char	*clear;

// 	if ((fd = open("/dev/tty", O_RDWR)) == -1)
// 		ft_error();
// 	ve = tgetstr("ve", 0);
// 	clear = tgetstr("cl", 0);
// 	tputs(ve, fd, &putchar_select);
// 	tputs(clear, fd, &putchar_select);
// 	ft_putstr_fd("\033[?1049l", fd);
// }

void		sig_exit(int x)
{
	int		n;
	t_init	*in;

	in = get_i(0);
	n = 26;

	/**
	 * ctrl+c = 2
	 */
	// ft_printf("%d", x);
	x = -1;
	// if (x == 2)
	// {

		return_terminal(in);
		close(in->fd);
		exit(EXIT_SUCCESS);


		// ft_putchar('\n');
		// ft_putstr("21sh%> ");




	// }
	// else
	// {
	// 	return_terminal(in);
	// 	close(in->fd);
	// 	exit(EXIT_SUCCESS);
	// }
	// else
	// {
	// 	ft_putchar('\n');
	// 	ft_putstr("21sh%> ");
	// 	// return_terminal(in);
	// 	// close(in->fd);
	// 	// exit(EXIT_SUCCESS);
	// }
}

void		signals(void)
{
	int		i;

	i = 0;
	while (++i < 100)
		signal(i, &sig_exit);
}
