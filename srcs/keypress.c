/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/18 11:34:31 by nriker            #+#    #+#             */
/*   Updated: 2020/05/17 01:20:46 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "ft_21sh.h"

// // void		just_key

// int			keypress(t_init *in, t_input *input, char buf[7])
// {
// 	int flag = 0;
// 	// ft_printf("%d %d %d %d", buf[0], buf[1], buf[2], buf[3]);
// 	/*
// 	** Pressed A-Z, or a-z, or 0-9
// 	*/
// 	if (!input->qt)
// 	{

// 		if ((((buf[0] == 32 && !buf[1] && !buf[2])
// 			|| (buf[0] == 39 && !buf[1] && !buf[2])
// 			|| (buf[0] == 34 && !buf[1] && !buf[2])
// 			|| (buf[0] >= 65 && buf[0] <= 90) || (buf[0] >= 97 && buf[0] <= 122)
// 			|| (buf[0] >= 48 && buf[0] <= 57)) && !buf[1] && !buf[2])
// 			|| (buf[0] == 46 && !buf[1] && !buf[2]))
// 		{
// 			if (input->flag)
// 				input->flag_qt = 0; //Флаг для пересчета позиции при flag qt
// 			if (!((input->width - 1) % input->col) && input->row == input->li
// 				&& input->x != input->width && !input->qt)
// 			{
// 				if (!input->old_row)
// 				{
// 					// ft_putstr("QQQ");
// 					input->y--;
// 					input->old_row = 0;
// 				}
// 			}

// 			if ((!((input->width) % input->col) && input->row < input->li))
// 			{
// 				if (input->row == input->li - 2)
// 					input->f = input->li - 2;
// 				if (input->row == input->li - 1)
// 					input->old = input->li - 1;
// 				input->row++;
// 			}

// 			if (!((input->width) % input->col))
// 				input->lines_in_com++;

// 			if (!(input->x % input->col) && input->y < input->row)
// 				input->y++;
				
// 			input->p_tab = 0;
// 			input->p_tab_part = 0;
// 			input->line = lineadd(&input->line, buf[0], input->x - input->index);
// 			if (input->x < input->width)
// 			{
// 				ft_putchar(buf[0]);
// 				ft_putstr(&input->line[input->x - 7]);
// 				if (!(input->width % input->col) && input->row == input->li
// 					&& !input->qt)
// 				{
// 					ft_putchar('\n');
// 					if (input->old != input->li - 1)
// 					{
// 						// ft_putstr("WWW");
// 						input->y--;
// 					}
// 					else if (input->o == 1)
// 					{
// 						flag = 1;
// 						// ft_putstr("EEE");
// 						input->y--;
// 						if (input->f)
// 							input->y++;
// 					}
// 					input->o = 0;
// 					input->old = 0;
// 					input->old_row = 1;
// 				}
// 				ft_printf("\e[%d;%dH", input->y, (input->x % input->col) + 1, input->y);
// 			}
// 			else
// 			{
// 				ft_putchar(buf[0]);
// 				if (!((input->x) % input->col) && !input->qt)
// 				{
// 					ft_putchar('\n');
// 					input->o = 1;
// 				}
// 				else if (input->width == input->col && input->row == input->li
// 					&& !input->qt)
// 				{
// 					ft_putchar('\n');
// 					input->y--;
// 				}
// 			}
// 			input->width++;
// 			input->x++;
// 		}
// 	}
// 	else if (input->quote)
// 	{
// 		if ((((buf[0] == 32 && !buf[1] && !buf[2])
// 			|| (buf[0] == 39 && !buf[1] && !buf[2])
// 			|| (buf[0] == 34 && !buf[1] && !buf[2])
// 			|| (buf[0] >= 65 && buf[0] <= 90) || (buf[0] >= 97 && buf[0] <= 122)
// 			|| (buf[0] >= 48 && buf[0] <= 57)) && !buf[1] && !buf[2])
// 			|| (buf[0] == 46 && !buf[1] && !buf[2]))
// 		{
// 			if (input->flag)
// 				input->flag_qt = 0; //Флаг для пересчета позиции при flag qt
// 			if (!((input->width_quote - 1) % input->col)
// 				&& input->row == input->li
// 				&& input->x_quote != input->width_quote)
// 			{
// 				// ft_putstr("WWWWW"); // переход с 26 на 27 стр
// 				if (!input->old_row)
// 				{
// 					input->y--;
// 					input->old_row = 0;
// 				}
// 			}

// 			if ((!((input->width_quote) % input->col) && input->row < input->li))
// 			{
// 				if (input->row == input->li - 2)
// 					input->f = input->li - 2;
// 				if (input->row == input->li - 1)
// 					input->old = input->li - 1;
// 				input->row++;
// 			}

// 			if (!((input->width_quote) % input->col))
// 			{
// 				input->lines_in_com++;
// 				input->qlines_in_com++;
// 				input->lines_in_qt++;
// 			}

// 			if (!(input->x_quote % input->col) && input->y < input->row)
// 				input->y++;
				
// 			input->p_tab = 0;
// 			input->p_tab_part = 0;
// 			input->line = lineadd(&input->line, buf[0], input->x - input->index);
// 			if (input->x_quote < input->width_quote)
// 			{
// 				ft_putchar(buf[0]);
// 				ft_putstr(&input->line[input->x - 7]);
// 				if (!(input->width_quote % input->col) && input->row == input->li)
// 				{
// 					ft_putchar('\n');
// 					// ft_putstr("QQQQ"); // создание 27 строки
// 					if (input->old != input->li - 1)
// 						input->y--;
// 					else if (input->o == 1)
// 					{
// 						input->y--;
// 						if (input->f)
// 							input->y++;
// 					}
// 					input->o = 0;
// 					input->old = 0;
// 					input->old_row = 1;
// 				}
// 				ft_printf("\e[%d;%dH", input->y, (input->x_quote % input->col) + 1);
// 			}
// 			else
// 			{
// 				ft_putchar(buf[0]);
// 				if (!(input->x_quote % input->col))
// 				{
// 					ft_putchar('\n');
// 					input->o = 1;
// 					// ft_putchar('Q');
// 				}
// 				else if (input->width_quote == input->col
// 					&& input->row == input->li)
// 				{
// 					ft_putchar('\n');
// 					input->y--;
// 					// ft_putchar('W');
// 				}
// 			}
// 			input->width++;
// 			input->x++;
// 			input->width_quote++;
// 			input->x_quote++;
// 		}
// 	}
// 	else if (input->dquote)
// 	{
// 		if ((((buf[0] == 32 && !buf[1] && !buf[2])
// 			|| (buf[0] == 39 && !buf[1] && !buf[2])
// 			|| (buf[0] == 34 && !buf[1] && !buf[2])
// 			|| (buf[0] >= 65 && buf[0] <= 90) || (buf[0] >= 97 && buf[0] <= 122)
// 			|| (buf[0] >= 48 && buf[0] <= 57)) && !buf[1] && !buf[2])
// 			|| (buf[0] == 46 && !buf[1] && !buf[2]))
// 		{
// 			if (input->flag)
// 				input->flag_qt = 0; //Флаг для пересчета позиции при flag qt
// 			if (!((input->width_dquote - 1) % input->col)
// 				&& input->row == input->li
// 				&& input->x_dquote != input->width_dquote)
// 			{
// 				// ft_putstr("WWWWW"); // переход с 26 на 27 стр
// 				if (!input->old_row)
// 				{
// 					input->y--;
// 					input->old_row = 0;
// 				}
// 			}

// 			if ((!((input->width_dquote) % input->col) && input->row < input->li))
// 			{
// 				if (input->row == input->li - 2)
// 					input->f = input->li - 2;
// 				if (input->row == input->li - 1)
// 					input->old = input->li - 1;
// 				input->row++;
// 			}

// 			if (!((input->width_dquote) % input->col))
// 			{
// 				input->lines_in_com++;
// 				input->dqlines_in_com++;
// 				input->lines_in_qt++;
// 			}

// 			if (!(input->x_dquote % input->col) && input->y < input->row)
// 				input->y++;
				
// 			input->p_tab = 0;
// 			input->p_tab_part = 0;
// 			input->line = lineadd(&input->line, buf[0], input->x - input->index);
// 			if (input->x_dquote < input->width_dquote)
// 			{
// 				ft_putchar(buf[0]);
// 				ft_putstr(&input->line[input->x - 7]);
// 				if (!(input->width_dquote % input->col) && input->row == input->li)
// 				{
// 					ft_putchar('\n');
// 					// ft_putstr("QQQQ"); // создание 27 строки
// 					if (input->old != input->li - 1)
// 						input->y--;
// 					else if (input->o == 1)
// 					{
// 						input->y--;
// 						if (input->f)
// 							input->y++;
// 					}
// 					input->o = 0;
// 					input->old = 0;
// 					input->old_row = 1;
// 				}
// 				ft_printf("\e[%d;%dH", input->y, (input->x_dquote % input->col) + 1);
// 			}
// 			else
// 			{
// 				ft_putchar(buf[0]);
// 				if (!(input->x_dquote % input->col))
// 				{
// 					ft_putchar('\n');
// 					input->o = 1;
// 				}
// 				else if (input->width_dquote == input->col
// 					&& input->row == input->li)
// 				{
// 					ft_putchar('\n');
// 					input->y--;
// 				}
// 			}
// 			input->width++;
// 			input->x++;
// 			input->width_dquote++;
// 			input->x_dquote++;
// 		}
// 	}
// 	return (1);
// }
