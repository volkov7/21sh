/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/04 07:21:16 by root              #+#    #+#             */
/*   Updated: 2020/07/04 14:57:54 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		delete_history_qt_between_width_col(t_input *input)
{
	ft_putstr("\e[1P");
	ft_putstr("\e[1A");
	ft_printf("\e[%dG", input->col);
	input->x_quote = input->col;
	input->y--;
}

void		delete_history_qt_between_width_n(t_input *input)
{
	ft_putstr("\e[1A");
	input->dflag--;
	input->x_quote = sub_get_x(input, 3);
	ft_printf("\e[%dG", input->x_quote);
	input->y--;
	input->sub_qt--;
}

void		delete_history_qt_between_width(t_input *input)
{
	if (input->line[input->x - (input->index + 1)] == '\n')
	{
		delete_history_qt_between_width_n(input);
	}
	else if (input->x_quote % input->col == 1)
	{
		delete_history_qt_between_width_col(input);
	}
	else
	{
		ft_putstr("\e[1D");
		input->x_quote--;
	}
	ft_putstr("\e[1P");
}

void		delete_history_qt_between_x_n(t_input *input)
{
	input->y--;
	if (input->dflag > 0)
		input->dflag--;
	if (input->sub_qt > 0)
		input->sub_qt--;
	input->x_quote = sub_get_x(input, 3);
	ft_printf("\e[%d;%dH", input->y, input->x_quote);
	ft_putstr("\e[J");
	// ft_putstr(&input->line[input->x - input->index]);
	print_history(input->next, &input->line[input->x - input->index], 0);
	ft_printf("\e[%d;%dH", input->y, input->x_quote);

	input->qlines_in_com--;
	input->lines_in_com--;
}

void		delete_history_qt_between_x_col(t_input *input)
{
	input->y--;
	ft_printf("\e[%d;%dH", input->y, input->col);
	ft_putstr("\e[J");
	// ft_putstr(&input->line[input->x - input->index]);
	print_history(input->next, &input->line[input->x - input->index], 0);
	ft_printf("\e[%d;%dH", input->y, input->col);
	input->x_quote = input->col;
}

void		delete_history_qt_between_x_not_col(t_input *input)
{
	input->x_quote--;
	ft_putstr("\e[1D");
	ft_putstr("\e[J");
	print_history(input->next, &input->line[input->x - input->index], 0);
	ft_printf("\e[%d;%dH", input->y, input->x_quote);
}

void		delete_history_qt_between_x(t_input *input)
{
	if (input->qt && input->line[input->x - (input->index + 1)] == '\n')
	{
		delete_history_qt_between_x_n(input);
	}
	else if (input->x_quote % input->col == 1)
	{
		delete_history_qt_between_x_col(input);
	}
	else
	{
		delete_history_qt_between_x_not_col(input);
	}
}

void		delete_history_qt_between(t_input *input)
{
	if (input->x == input->width)
	{
		delete_history_qt_between_width(input);
	}
	else if ((input->flag && input->qt && input->x > input->index))
	{
		delete_history_qt_between_x(input);
	}
	input->x--;
	input->width--;
	input->width_dquote--;
	// if (input->hdoc)
	// 	input->x_hdoc--;
	if (!(input->width % input->col))
	{
		input->lines_in_com--;
		input->row--;
	}
	input->line = lineremove(input->line, input->x - input->index);
}

void		delete_letter_x_col(t_input *input)
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

void		delete_letter_x_not_col(t_input *input)
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

void		delete_letter_x(t_input *input)
{
	if (input->x % input->col == 1)
		delete_letter_x_col(input);
	else
		delete_letter_x_not_col(input);
}

void		delete_letter_width(t_input *input)
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

void		delete_letter(t_input *input)
{
	if (input->x == input->width)
		delete_letter_width(input);
	else if (input->x < input->width)
		delete_letter_x(input);
	input->x--;
	input->width--;
	if (!(input->width % input->col))
	{
		input->lines_in_com--;
		input->row--;
	}
	input->line = lineremove(input->line, input->x - input->index);
}

void		delete_quote_width(t_input *input)
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

void		delete_quote_x_col(t_input *input)
{
	ft_putstr("\e[1A");
	ft_printf("\e[%dG", input->col);
	input->y--;
	ft_putstr(&input->line[input->x - input->index]);
	ft_putchar(' ');
	ft_printf("\e[%d;%dH", input->y, input->col);
}

void		delete_quote_x_not_col(t_input *input)
{
	ft_putstr("\e[1D");
	ft_putstr(&input->line[input->x - input->index]);
	ft_putchar(' ');
	if (!(input->x_quote % input->col))
		ft_printf("\e[%d;%dH", input->y, input->col - 1);
	else
		ft_printf("\e[%d;%dH", input->y, (input->x_quote % input->col) - 1);
}

void		delete_quote_x(t_input *input)
{
	if (input->x_quote % input->col == 1)
		delete_quote_x_col(input);
	else
		delete_quote_x_not_col(input);

}

void		delete_quote(t_input *input)
{
	if (input->x_quote == input->width_quote)
		delete_quote_width(input);
	else if (input->x_quote < input->width_quote)
		delete_quote_x(input);
	input->x--;
	input->width--;
	input->x_quote--;
	input->width_quote--;
	if (!(input->width_quote % input->col))
	{
		input->lines_in_qt--;
		input->lines_in_com--;
		input->qlines_in_com--;
		input->row--;
	}
	input->line = lineremove(input->line, input->x - input->index);
}

void		delete_dquote_width(t_input *input)
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

void		delete_dquote_x_col(t_input *input)
{
	ft_putstr("\e[1A");
	ft_printf("\e[%dG", input->col);
	input->y--;
	ft_putstr(&input->line[input->x - 8]);
	ft_putchar(' ');
	ft_printf("\e[%d;%dH", input->y, input->col);
}

void		delete_dquote_x_not_col(t_input *input)
{
	ft_putstr("\e[1D");
	ft_putstr(&input->line[input->x - 8]);
	ft_putchar(' ');
	if (!(input->x_dquote % input->col))
		ft_printf("\e[%d;%dH", input->y, input->col - 1);
	else
		ft_printf("\e[%d;%dH", input->y, (input->x_dquote % input->col) - 1);
}

void		delete_dquote_x(t_input *input)
{
	if (input->x_dquote % input->col == 1)
		delete_dquote_x_col(input);
	else
		delete_dquote_x_not_col(input);
}

void		delete_dquote(t_input *input)
{
	if (input->x_dquote == input->width_dquote)
		delete_dquote_width(input);
	else if (input->x_dquote < input->width_dquote)
		delete_dquote_x(input);
	input->x--;
	input->width--;
	input->x_dquote--;
	input->width_dquote--;
	if (!(input->width_dquote % input->col))
	{
		input->lines_in_qt--;
		input->lines_in_com--;
		input->dqlines_in_com--;
		input->row--;
	}
	input->line = lineremove(input->line, input->x - input->index);
}

int			delete_press(t_init *in, t_input *input, char buf[7])
{
	if ((buf[0] == 127 && !buf[1] && !buf[2]))
	{
		input->p_tab = 0;
		input->p_tab_part = 0;
		input->flag_qt = 0;
		if (input->flag && input->qt && input->x > input->index)
		{
			delete_history_qt_between(input);
		}
		else if (input->x > input->index && !input->qt)
		{
			delete_letter(input);
		}
		else if (input->x_quote > input->index && !input->flag)
		{
			delete_quote(input);
		}
		else if (input->x_dquote > 9 && !input->flag)
		{
			delete_dquote(input);
		}
	}
	return (1);
}
