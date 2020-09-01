/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/31 06:35:46 by nriker            #+#    #+#             */
/*   Updated: 2020/08/02 10:35:11 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"
#include "lexer.h"

void	set_keypress(t_init *in)
{
	if ((tgetent(NULL, in->terminal)) == -1)
		ft_error();
	if ((tcgetattr(0, &in->tr) == -1))
		ft_error_select(0);
	if ((tcgetattr(0, &in->old_tr) == -1))
		ft_error_select(0);
	in->tr.c_lflag &= (~ICANON);
	in->tr.c_lflag &= (~ICANON);
	in->tr.c_lflag &= (~ECHO);
	in->tr.c_cc[VTIME] = 10;
	in->tr.c_cc[VMIN] = 1;
	if (tcsetattr(0, TCSANOW, &in->tr) == -1)
		ft_error();
}

int		main(int argc, char **argv, char **env)
{
	t_init			in;
	t_input			*input;
	t_envlist		*envlst;

	input = NULL;
	envlst = NULL;
	argv[0] = "";
	if (argc > 1)
		ft_error_select(1);
	signals();
	create_init(&in);
	set_keypress(&in);
	init_env(env, &envlst);
	get_envlst(envlst);
	main_cycle(&in, input);
	exit(1);
}
