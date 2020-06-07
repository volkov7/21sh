/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 12:31:34 by nriker            #+#    #+#             */
/*   Updated: 2020/05/24 12:49:56 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

// int			specialpress(t_init *in, t_input *input, char buf[7])
// {
// 	/*
// 	** Pressed CTRL+A/HOME - to start of the line
// 	*/
// 	if ((buf[0] == 1 && !buf[1] && !buf[2])
// 		|| (buf[0] == 27 && buf[1] == 91 && buf[2] == 72 && !buf[3]))
// 	{
// 		if (!input->qt)
// 		{
// 			input->y = input->row - (input->lines_in_com - 1);
// 			input->x = 8;
// 		}
// 		else if (input->quote)
// 		{
// 			input->y = input->row - (input->qlines_in_com - 1);
// 			input->x -= input->width_quote - 8;
// 			input->x_quote = 8;
// 		}
// 		else if (input->dquote)
// 		{
// 			input->y = input->row - (input->dqlines_in_com - 1);
// 			input->x -= input->width_dquote - 9;
// 			input->x_dquote = 9;
// 			ft_printf("\e[%d;9H", input->y);
// 		}
// 		if (!input->qt || input->quote)
// 			ft_printf("\e[%d;8H", input->y);
// 	}
// 	/*
// 	** Pressed CTRL+E/END - to end of the line
// 	*/
// 	else if ((buf[0] == 5 && !buf[1] && !buf[2])
// 			|| (buf[0] == 27 && buf[1] == 91 && buf[2] == 70 && !buf[3]))
// 	{
// 		input->y = input->row;
// 		input->x = input->width;
// 		if (!input->qt)
// 		{
// 			if (!(input->x % input->col))
// 				ft_printf("\e[%d;%dH", input->y, input->col);
// 			else
// 				ft_printf("\e[%d;%dH", input->y, input->x % input->col);
// 		}
// 		else if (input->quote)
// 		{
// 			input->x_quote = input->width_quote;
// 			if (!(input->x_quote % input->col))
// 				ft_printf("\e[%d;%dH", input->y, input->col);
// 			else
// 				ft_printf("\e[%d;%dH", input->y, input->x_quote % input->col);
// 		}
// 		else if (input->dquote)
// 		{
// 			input->x_dquote = input->width_dquote;
// 			if (!(input->x_dquote % input->col))
// 				ft_printf("\e[%d;%dH", input->y, input->col);
// 			else
// 				ft_printf("\e[%d;%dH", input->y, input->x_dquote % input->col);
// 		}
// 	}
// 	/*
// 	** Pressed CTRL+K - delete all chars after cursor
// 	*/

// 	/*
// 	** Pressed CTRL+D
// 	*/
// 	else if (buf[0] == 4 && buf[1] == 0 && buf[2] == 0 && buf[3] == 0)
// 	{
// 		return_terminal(in);
// 		close(in->fd);
// 		free_input(input);
// 		free_init(in);
// 		exit(EXIT_SUCCESS);
// 	}
// 	/*
// 	** Pressed CTRL+L - clear window pf terminal
// 	*/
// 	else if (buf[0] == 12 && buf[1] == 0 && buf[2] == 0 && buf[3] == 0)
// 	{
// 		ft_putstr("\e[2J");
// 		ft_putstr("\e[H");
// 		input->c = input->width + 1;
// 		input->row = 1;
// 		while ((input->c -= input->col) > 0)
// 			input->row++;
// 		if (input->quote)
// 			input->c = input->x_quote + 1;
// 		else if (input->dquote)
// 			input->c = input->x_dquote + 1;
// 		else
// 			input->c = input->x + 1;
// 		input->y = 1;
// 		while ((input->c -= input->col) > 0)
// 			input->y++;
// 		if (input->width_quote)
// 		{
// 			// input->x_quote = 7;
// 			// input->width_quote = 7;
// 			ft_putstr("quote> ");
// 			if (input->flag)
// 				ft_putstr("\e[s");
// 			ft_putstr(ft_strrchr(input->line, '\n') + 1);
// 			// if (!ft_strlen(&input->line[input->width_quote - 9]))
// 				// ft_printf("\e[%d;%dH", input->y, input->x_quote % input->col);
// 			// else
// 				// ft_printf("\e[%d;%dH", input->y, (input->x_quote % input->col));
// 		}
// 		else if (input->width_dquote)
// 		{
// 			// input->x_dquote = 8;
// 			// input->width_dquote = 8;
// 			ft_putstr("dquote> ");
// 			if (input->flag)
// 				ft_putstr("\e[s");
// 			ft_putstr(ft_strrchr(input->line, '\n') + 1);
// 			// if (!ft_strlen(&input->line[input->width_dquote - 10]))
// 				// ft_printf("\e[%d;%dH", input->y, input->x_dquote % input->col);
// 			// else
// 				// ft_printf("\e[%d;%dH", input->y, (input->x_dquote % input->col));
// 		}
// 		else
// 		{
// 			ft_putstr("21sh%> ");
// 			if (input->flag)
// 				ft_putstr("\e[s");
// 			ft_putstr(input->line);
// 			// if (!ft_strlen(input->line))
// 				// ft_printf("\e[%d;%dH", input->y, input->x % input->col);
// 			// else
// 				// ft_printf("\e[%d;%dH", input->y, (input->x % input->col + 1));
// 		}
// 		ft_printf("\e[%d;%dH", input->y, input->x % input->col);
// 	}
// 	/*
// 	** Pressed CTRL+U
// 	*/
// 	else if (buf[0] == 21 && !buf[1] && !buf[2])
// 	{
// 		if (!input->qt)
// 			ft_printf("\e[%d;8H", input->row - input->lines_in_com + 1);
// 		else if (input->quote)
// 			ft_printf("\e[%d;8H", input->row - input->qlines_in_com + 1);
// 		else
// 			ft_printf("\e[%d;9H", input->row - input->dqlines_in_com + 1);
// 		ft_putstr("\e[J");
// 		if (input->x_quote)
// 		{
// 			input->x -= input->width_quote - 8;
// 			// input->width -= input->width_quote - 8;
// 			while (input->width_quote-- > 8)
// 			{
// 				input->line = lineremove(input->line, input->width - (input->index - 1));
// 				input->width--;
// 			}
// 			input->x_quote = 8;
// 			input->width_quote = 8;
// 			if (input->qlines_in_com > 1)
// 				input->lines_in_com -= input->qlines_in_com;
// 			input->qlines_in_com = 1;
// 		}
// 		else if (input->dquote)
// 		{
// 			input->x -= input->width_dquote - 9;
// 			// input->width -= input->width_dquote - 8;
// 			while (input->width_dquote-- > 9)
// 			{
// 				input->line = lineremove(input->line, input->width - (( - input->index - 1)));
// 				input->width--;
// 			}
// 			input->x_dquote = 9;
// 			input->width_dquote = 9;
// 			if (input->dqlines_in_com > 1)
// 				input->lines_in_com -= input->dqlines_in_com;
// 			input->dqlines_in_com = 1;
// 		}
// 		else
// 		{
// 			if (ft_strlen(input->line))
// 			{
// 				free(input->line);
// 				input->line = ft_strdup("");
// 			}
// 			input->x = 8;
// 			input->width = 8;
// 			input->lines_in_com = 1;
// 		}
// 		input->y = get_curs_row();
// 		input->row = input->y;
// 	}
// 	/*
// 	** Pressed TAB
// 	*/
// 	else if (buf[0] == 9 /*&& !buf[1] && !buf[2] && !buf[3]*/)
// 	{
// 		// putchar('Q');
// 		press_tab(in, input);
// 		// return (0);
// 	}
// 	/*
// 	** Pressed ESC
// 	*/
// 	// else if (buf[0] == 46 && !buf[1] && !buf[2])
// 	// {
// 	// 	// ft_putstr("!\n");
// 	// 	// while (input)
// 	// 	// {
// 	// 	// 	ft_putstr(input->line);
// 	// 	// 	input = input->next;
// 	// 	// }
		
// 	// 	// ft_putstr("\e[s");
// 	// 	// ft_printf("%d", input->x);
// 	// 	// ft_printf("com %d col %d x %d, row %d y %d w %d col %d q %d dq %d", input->lines_in_com, input->col, input->x, input->row, input->y, input->width, input->col, input->x_quote, input->x_dquote);
// 	// 	ft_printf("%d %d %d", input->dflag, input->sub_qt, input->flag);
// 	// }
// 	else if (buf[0] == 47 && !buf[1] && !buf[2])
// 	{
// 		// ft_printf("%d %d %d %d %d %d %d", input->flag, input->qt, input->x, input->width, input->y, input->x_quote, input->width_quote);
// 		// ft_printf("%d", input->x_quote);
// 		input->p_tab = 1;
// 		// ft_printf("%d %d %d %d", input->x, input->x_quote, input->y, input->width, input-> row);

// 		// ft_printf("%d %d %d %d", input->x, input->x_quote, input->width_quote, input->width);

// 		// return_curstostart_str(input, input->width);

// 		// ft_putchar('Q');
// 		// ft_printf("%d", input->lines_in_com);
// 		// ft_putstr("\e[u");
// 		// ft_printf("%d %d %d %d", input->x, input->width, input->x_quote, input->y, input->flag);
// 		// ft_printf("%d", input->len_qt);
// 		// ft_printf("wq %d wdq %d l %d ql %d dql %d", input->width_quote, input->width_dquote, input->lines_in_com, input->qlines_in_com, input->dqlines_in_com);
// 		// ft_putstr("\e[u");
// 		// ft_printf("%d %d %d %d", input->prev->x, input->quote, input->save_x, input->width);
// 		// ft_putstr(input->line);
// 	}
// 	return (1);
// }
/*
** Pressed ENTER
*/

void		*get_command_params_qt(t_input *input, t_input *old_input, int len)
{
	if (input->quote)
		input->width_quote = len + input->index;
	else if (input->dquote)
		input->width_dquote = len + input->index;
	input->width = ft_strlen(input->line) + input->index;
	input->x = input->width;
	input->y = get_curs_row();
	if (input->quote)
	{
		input->x_quote = input->width_quote;
		input->qlines_in_com = old_input->lines_in_com;
		input->lines_in_com = input->lines_in_com + input->qlines_in_com;
	}
	else if (input->dquote)
	{
		input->x_dquote = input->width_dquote;
		input->dqlines_in_com = old_input->lines_in_com;
		input->lines_in_com = input->lines_in_com + input->dqlines_in_com;
	}
}

t_input		*insert_history_line(t_input *input)
{
	char	*str;
	char	*str2;
	char	*str3;
	int		len;
	t_input	*old_input;

	old_input = input;
	str = ft_strcut(input->line, '\n');
	while (input && input->prev)
		input = input->prev;
	str2 = ft_strrchr(input->line, '\n') + 1;
	len = (ft_strlen(input->line) - ft_strlen(str2)) + 1;
	str3 = ft_strnew(len);
	ft_strncpy(str3, input->line, len - 1);
	if (input->quote)
		input->lines_in_com = input->lines_in_com - input->qlines_in_com;
	else if (input->dquote)
		input->lines_in_com = input->lines_in_com - input->dqlines_in_com;
	free(input->line);
	len = ft_strlen(str);
	input->line = ft_strjoinfreefree(str3, str);
	get_command_params_qt(input, old_input, len);
	return (input);
}

int			check_flag_qt(t_input *input)
{
	while (input && input->prev)
		input = input->prev;
	if (input->qt)
		return (1);
	return (0);
}

int			enter_press(t_init *in, t_input *input, char buf[7])
{
	char	*copy;
	int 	x;

	if ((buf[0] == 13 || buf[0] == 10) && !buf[1])
	{
		
		// if (input->flag && check_flag_qt(input))
		// {
		// 	// ft_printf("!%s!", input->line);
		// 	input = insert_history_line(input);
		// 	// ft_printf("!%s!", input->line);
			
		// }
		
		// if (input->qt)
		// {
		// 	char	buf[7];
		// 	ft_printf("!%s! %d %d %d", input->line, input->x, input->index, input->width);
		// 	if (read(0, buf, 7) == -1)
		// 				ft_error();
		// }
		fill_new_input(input);
		get_curs_pos_inend(input);
		// if (check_quotes(input))
		// 	ft_printf("!%s!", input->line);
		// if (input->qt)
		// {
		// 	char	buf[7];
		// 	ft_printf("!%s!", input->line);
		// 	if (read(0, buf, 7) == -1)
		// 				ft_error();
		// }
		if (!check_quotes(input))
		{
			if (input->hdoc)
			{
				if (!input->qt)
				{
					if (!ft_strchr(input->line, '\n'))
						if (input->line[input->x - input->index] != '\n')
							input->line = lineadd(&input->line, '\n', input->width - input->index);
				}
				else if (input->line[input->width - input->index] != '\n')///changed x -> width
					input->line = lineadd(&input->line, '\n', input->width - input->index);
			}
			// if (input->p_tab || input->list_size)
			// 	clear_tab_output(in, input);
			return (0);
		}
		input->qt = 1;
		input->x = input->width;
		// if (input->qt)
		// {
		// 	char	buf[7];
		// 	ft_printf("!%s! %d %d %d", input->line, input->x, input->index, input->width);
		// 	if (read(0, buf, 7) == -1)
		// 				ft_error();
		// }
		input->line = lineadd(&input->line, '\n', input->x - input->index);
		// if (input->qt)
		// {
		// 	char	buf[7];
		// 	ft_printf("!%s!", input->line);
		// 	if (read(0, buf, 7) == -1)
		// 				ft_error();
		// }
		input->x++;
		input->width++;
		input->lines_in_qt = 1;
		input->qlines_in_com = 1;
		input->dqlines_in_com = 1;
		input->lines_in_com++;
		input->sub_qt++;
		if (input->quote)
		{
			
			// if (input->y < input->row)
			// 	ft_printf("%\e[%dE", input->row - input->y);
			// ft_printf("\e[%d;%dH2", input->row, input->width % input->col);
			ft_putstr("\nquote> ");
			if (input->row < input->col)
				input->row++;
			input->y = input->row;
			input->x_quote = 8;
			input->width_quote = 8;
			// input->index = 8;//!!!!!!!!!!!!!!!!!!!
			// input->len += 7;
			// input->x_dquote = 0;
			input->width_dquote = 0;
			input->old_row = 0;
			input->old = 0;
			input->o = 0;
			input->f = 0;
			// char	bufq[7];
			// ft_printf("!%s!", input->line);
			// if (read(0, bufq, 7) == -1)
			// 		ft_error();
		}
		else if (input->dquote)
		{
			ft_printf("\e[%d;%dH", input->row, input->width % input->col);
			ft_putstr("\ndquote> ");
			if (input->row < tgetnum("li"))
				input->row++;
			input->y = input->row;
			input->x_quote = 0;
			input->width_quote = 0;
			// input->len += 8;
			input->x_dquote = 9;
			input->width_dquote = 9;
			// input->index = 9;//!!!!!!!!!!!!!!!!!!!
			input->old_row = 0;
			input->old = 0;
			input->o = 0;
			input->f = 0;
		}
		// if (input->flag)
		// 	while (1);
		// ft_printf("%s", input->line);
	}
	return (1);
}


/*
** Pressed DELETE 
*/
int			delete_press(t_init *in, t_input *input, char buf[7])
{
	if ((buf[0] == 127 && !buf[1] && !buf[2]))
	{
		input->p_tab = 0;
		input->p_tab_part = 0;
		input->flag_qt = 0;
		if (input->flag && input->qt && input->x > input->index)
		{
			if (input->x == input->width)
			{
				if (input->line[input->x - (input->index + 1)] == '\n')
				{
					ft_putstr("\e[1A");
					input->dflag--;
					input->x_quote = sub_get_x(input, 3);
					ft_printf("\e[%dG", input->x_quote);
					input->y--;
					input->sub_qt--;
				}
				else if (input->x_quote % input->col == 1)
				{
					ft_putstr("\e[1P");
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
				ft_putstr("\e[1P");
			}
			else if ((input->flag && input->qt && input->x > input->index))
			{
				if (input->qt && input->line[input->x - (input->index + 1)] == '\n')
				{
					input->y--;
					if (input->dflag > 0)
						input->dflag--;
					if (input->sub_qt > 0)
						input->sub_qt--;
					input->x_quote = sub_get_x(input, 3);
					ft_printf("\e[%d;%dH", input->y, input->x_quote);
					ft_putstr("\e[J");
					ft_putstr(&input->line[input->x - input->index]);
					ft_printf("\e[%d;%dH", input->y, input->x_quote);
				}
				else if (input->x_quote % input->col == 1)
				{
					input->y--;
					ft_printf("\e[%d;%dH", input->y, input->col);
					ft_putstr("\e[J");
					ft_putstr(&input->line[input->x - input->index]);
					ft_printf("\e[%d;%dH", input->y, input->col);
					input->x_quote = input->col;
				}
				else
				{
					input->x_quote--;
					ft_putstr("\e[1D");
					ft_putstr("\e[J");
					ft_putstr(&input->line[input->x - input->index]);
					ft_printf("\e[%d;%dH", input->y, input->x_quote);
				}
			}
			input->x--;
			input->width--;
			// if (input->hdoc)
			// 	input->x_hdoc--;
			if (!(input->width % input->col))
			{
				input->lines_in_com--;
				input->row--;
			}
			input->line = lineremove(input->line, input->x - input->index);
		}
		else if (input->x > input->index && !input->qt)
		{
			if (input->x == input->width)
			{
				if (input->x % input->col == 1)
				{
					ft_putstr("\e[1A");
					ft_printf("\e[%dG", input->col);
					input->y--;
				}
				else
					ft_putstr("\e[1D");
				ft_putstr("\e[1P");
			}
			else if (input->x < input->width)
			{
				if (input->x % input->col == 1)
				{
					ft_putstr("\e[1A");
					ft_printf("\e[%dG", input->col);
					input->y--;
					if (input->flag)
					{
						char	*str;
						str = ft_strcut(input->line, '\n');
						ft_putstr(&str[input->x - input->index]);
						free(str);
					}
					else
						ft_putstr(&input->line[input->x - input->index]);
					ft_putchar(' ');
					ft_printf("\e[%d;%dH", input->y, input->col);
				}
				else
				{
					char	*str;

					ft_putstr("\e[1D");
					if (ft_strchr(input->line, '\n'))
					{
						str = ft_strcut(input->line, '\n');
						ft_putstr(&str[input->x - input->index]);
						free(str);
					}
					else
						ft_putstr(&input->line[input->x - input->index]);
					ft_putchar(' ');
					if (!(input->x % input->col))
						ft_printf("\e[%d;%dH", input->y, input->col - 1);
					else
						ft_printf("\e[%d;%dH", input->y, (input->x % input->col) - 1);
				}
			}
			input->x--;
			input->width--;
			if (!(input->width % input->col))
			{
				input->lines_in_com--;
				input->row--;
			}
			input->line = lineremove(input->line, input->x - input->index);
		}
		else if (input->x_quote > input->index && !input->flag)
		{
			if (input->x_quote == input->width_quote)
			{
				if (input->x_quote % input->col == 1)
				{
					ft_putstr("\e[1A");
					ft_printf("\e[%dG", input->col);
					// input->line = lineremove(input->line, input->x_quote - 1);
					input->y--;
				}
				else
					ft_putstr("\e[1D");
				ft_putstr("\e[1P");
			}
			else if (input->x_quote < input->width_quote)
			{
				if (input->x_quote % input->col == 1)
				{
					ft_putstr("\e[1A");
					ft_printf("\e[%dG", input->col);
					input->y--;
					ft_putstr(&input->line[input->x - input->index]);
					ft_putchar(' ');
					ft_printf("\e[%d;%dH", input->y, input->col);
				}
				else
				{
					ft_putstr("\e[1D");
					ft_putstr(&input->line[input->x - input->index]);
					ft_putchar(' ');
					if (!(input->x_quote % input->col))
						ft_printf("\e[%d;%dH", input->y, input->col - 1);
					else
						ft_printf("\e[%d;%dH", input->y, (input->x_quote % input->col) - 1);
				}
			}
			input->x--;
			input->width--;
			input->x_quote--;
			input->width_quote--;
			if (!(input->width_quote % input->col))
			{
				input->lines_in_qt--;
				input->qlines_in_com--;
				input->row--;
			}
			input->line = lineremove(input->line, input->x - input->index);
		}
		else if (input->x_dquote > 9 && !input->flag)
		{
			if (input->x_dquote == input->width_dquote)
			{
				if (input->x_dquote % input->col == 1)
				{
					ft_putstr("\e[1A");
					ft_printf("\e[%dG", input->col);
					// input->line = lineremove(input->line, input->x_dquote - 1);
					input->y--;
				}
				else
					ft_putstr("\e[1D");
				ft_putstr("\e[1P");
			}
			else if (input->x_dquote < input->width_dquote)
			{
				if (input->x_dquote % input->col == 1)
				{
					ft_putstr("\e[1A");
					ft_printf("\e[%dG", input->col);
					input->y--;
					ft_putstr(&input->line[input->x - 8]);
					ft_putchar(' ');
					ft_printf("\e[%d;%dH", input->y, input->col);
				}
				else
				{
					ft_putstr("\e[1D");
					ft_putstr(&input->line[input->x - 8]);
					ft_putchar(' ');
					if (!(input->x_dquote % input->col))
						ft_printf("\e[%d;%dH", input->y, input->col - 1);
					else
						ft_printf("\e[%d;%dH", input->y, (input->x_dquote % input->col) - 1);
				}
			}
			input->x--;
			input->width--;
			input->x_dquote--;
			input->width_dquote--;
			if (!(input->width_dquote % input->col))
			{
				input->lines_in_qt--;
				input->dqlines_in_com--;
				input->row--;
			}
			input->line = lineremove(input->line, input->x - input->index);
		}
	}
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 51 && buf[3] == 126
		&& !buf[4])
	{
		input->p_tab = 0;
		input->p_tab_part = 0;
		if (input->x < input->width && !input->qt)
		{
			ft_putstr(&input->line[input->x - (input->index - 1)]);
			ft_putchar(' ');
			if (input->x == input->col)
				ft_printf("\e[%d;%dH", input->y, input->col);
			else
				ft_printf("\e[%d;%dH", input->y, (input->x % input->col));
			// input->len--;
			// input->len_x--;
			input->width--;
			if (!(input->width % input->col))
			{
				input->lines_in_com--;
				input->row--;
			}
			input->line = lineremove(input->line, input->x - input->index);
		}
		else if (input->x_quote < input->width_quote)
		{
			ft_putstr(&input->line[input->x - (input->index - 1)]);
			ft_putchar(' ');
			if (input->x_quote == input->col)
				ft_printf("\e[%d;%dH", input->y, input->col);
			else
				ft_printf("\e[%d;%dH", input->y, (input->x_quote % input->col));
			// input->len--;
			// input->len_x--;
			input->width_quote--;
			if (!(input->width % input->col))
			{
				input->lines_in_qt--;
				input->dqlines_in_com--;
				input->lines_in_com--;
				input->row--;
			}
			input->line = lineremove(input->line, input->x - input->index);
		}
		else if (input->x_dquote < input->width_dquote)
		{
			ft_putstr(&input->line[input->x - (input->index - 1)]);
			ft_putchar(' ');
			if (input->x_dquote == input->col)
				ft_printf("\e[%d;%dH", input->y, input->col);
			else
				ft_printf("\e[%d;%dH", input->y, (input->x_dquote % input->col));
			// input->len--;
			// input->len_x--;
			input->width_dquote--;
			if (!(input->width_dquote % input->col))
			{
				input->lines_in_qt--;
				input->dqlines_in_com--;
				input->lines_in_com--;
				input->row--;
			}
			input->line = lineremove(input->line, input->x - input->index);
		}
	}
	return (1);
}

t_input		*read_input(t_init *in, t_input *input)
{
	t_input		*copy;
	char		buf[7];

	ft_bzero((void*)buf, 7);
	while (1)
	{
		if (read(0, buf, 7) == -1)
			ft_error();
			// ft_printf("%d %d %d %d", buf[0], buf[1], buf[2], buf[3]);
		// if (buf[0] == 47 && !buf[1] && !buf[2])
		// {
		// 	ft_printf("%d %d %d %d", input->x, input->width, input->width_quote, input->lines_in_com, input->qlines_in_com);
		// 	while (1);
		// }
		
		// if (buf[0] == 27 && buf[1] == 91 && buf[2] == 72 && !buf[3])
		// {
		// 	specialpress(in, input, buf);
		// }
		
		// specialpress(in, input, buf);
		if ((buf[0] == 13 || buf[0] == 10) && !buf[1]
			&& input->flag && check_flag_qt(input))
			input = insert_history_line(input);
		if (buf[0] == 27 && buf[1] == 91 && (buf[2] == 65 || buf[2] == 66
				|| buf[2] == 67 || buf[2] == 68))
			input = arrowpress(in, input, buf);
		else if (!letterpress(in, input, buf) || !delete_press(in, input, buf)
			|| !specialpress(in, input, buf) || !enter_press(in, input, buf))
			return (input);
		ft_bzero((void*)buf, 7);
	}
	return (input);
}
