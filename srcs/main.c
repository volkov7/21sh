/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 16:13:48 by nriker            #+#    #+#             */
/*   Updated: 2020/05/24 10:48:58 by root             ###   ########.fr       */
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
	// tputs(tgetstr("im", NULL), in->fd, &putchar_select);
}

int		check_command(t_input *input)
{
	int		len;
	int		x;

	x = -1;
	len = ft_strlen(input->line);
	while (++x < len)
		if (input->line[x] != ' ' && input->line[x] != '\n')
			return (0);
	return (1);
}

int		main(int argc, char **argv, char **env)
{
	t_init			in;
	t_input			*input;
	t_input			*copy;
	t_envlist		*envlst = NULL;

	input = NULL;
	init_env(env, &envlst);
	argv[0] = "";
	if (argc > 1)
		ft_error_select(1);
	// signals();
	create_init(&in);
	set_keypress(&in);
	while (1)
	{
		ft_putstr("21sh%> ");
		if (!input)
		{
			while (1)
			{
				input = create_input();
				input = read_input(&in, input);
				if (ft_strlen(input->line) && ft_strcmp(input->line, "\n")
					&& !check_command(input))
				{
					//Iliya! Insert your functions instead ft_printf, use pointer input->line
					ft_putchar('\n');
					input->line = lineadd(&input->line, '\n', input->width - input->index);
					prepare_lexer(input->line, &envlst, &in, input);

					// ft_printf("\n%s\n", input->line);
					break;
				}
				free_input(input);
				ft_putstr("\n21sh%> ");
			}
		}
		else
		{
			
			input->prev = create_input();
			input->prev->next = input;
			input = input->prev;
			copy = copyinput(input);
			in.input = input;
			while (1)
			{
				copy = read_input(&in, copy);
				if (ft_strlen(copy->line) && ft_strcmp(copy->line, "\n")
					&& !check_command(copy))
				{
					copy_struct_history(copy, input);
					free_input(copy);
					//Iliya! Insert your functions instead ft_printf, use pointer input->line
					ft_putchar('\n');
					if (input->line[input->x - 8] != '\n')
						input->line = lineadd(&input->line, '\n', input->width - input->index);
					if (!ft_strcmp(input->line, "lol\n"))
					{
						read_input_heredoc(&in, input, 2);
						ft_printf("!%s!", input->line);
						while (1);
					}
					// else if (!ft_strcmp(input->line, "lol2\n"))
					// {
					// 	read_input_heredoc(&in, input, 1);
					// 	ft_printf("!%s!", input->line);
					// 	while (1);
					// } 
					// ft_printf("!%s!", input->line);
					// 	while (1);
					prepare_lexer(input->line, &envlst, &in, input);
					// ft_printf("\n%s\n", input->line);
					break;
				}
				free_input(copy);
				copy = copyinput(input);
				ft_putstr("\n21sh%> ");
			}
		}
	}
	exit(1);
}
