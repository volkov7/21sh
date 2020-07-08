/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_substitution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:13:28 by nriker            #+#    #+#             */
/*   Updated: 2020/07/04 15:09:33 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		get_index_for_clear(t_input *input)
{
	int index;

	input->c2 = 99;
	if (input->hdoc)
	{
		if (!input->prev)
			input->c2 = input->index;
		else
		{
			while (input && input->prev)
				input = input->prev;
			index = input->index;
			while (input && input->c2 != 99)
				input = input->next;
			input->c2 = index;
		}
	}
	else
		input->c2 = input->index;
}

int			check_plus(t_input *input)
{
	if (input->qt && !input->next->qt && input->next->lines_in_com == 1)
		return (0);
	return (1);
}

void		print_last_input_qt(t_input *input)
{
	if (input->quote)
		ft_printf("\e[%d;%dH", input->c - input->qlines_in_com + 1, input->c2);
	else if (input->dquote)
		ft_printf("\e[%d;%dH", input->c - input->dqlines_in_com + 1, input->c2);
}

void		clear_last_input(t_input *input)
{
	get_curs_pos_inend(input);
	input->c = get_curs_row();
	get_index_for_clear(input);
	e++;
	if (!input->flag && input->qt)
	{
		// while (1);
		// if (e > 3)
		// {
		// 	while (1);
		// }

			// ft_printf("!%d %d %d ?%d?!", input->qt, input->flag, input->c, input->lines_in_com);

		if (input->quote)
			ft_printf("\e[%d;%dH", input->c - input->qlines_in_com + 1, input->c2);
		else if (input->dquote)
			ft_printf("\e[%d;%dH", input->c - input->dqlines_in_com + 1, input->c2 + 1);
	}
	// else if (input->flag && input->qt)
	// {
	// 	print_last_input_qt(input);
	// }
	else
	{ 
		ft_printf("\e[%d;%dH", input->c - input->lines_in_com + 1, input->c2);
	}
	

	ft_putstr("\e[J");
}

void		print_history(t_input *input, char *str, int x)
{
	char	*line;

	if (!ft_strlen(str))
		return ;
	if (ft_strchr(str, '\n'))
	{
		if (!(line = ft_strnew(ft_strlen(str))))
			return ;
		line = ft_strncpy(line, str, ft_strlen(str) - 1);
		ft_putstr(line);
		if (x && !((ft_strlen(line) + input->index - 1) % input->col))
			ft_putchar('\n');
		free(line);
	}
	else
		ft_putstr(str);
}

void		check_qt(t_input *input)
{
	int	x;
	int	x2;
	int	c;
	int	len;

	len = ft_strlen(input->line) - 1;
	c = input->x;
	x = 0;
	x2 = 7;
	input->c = 8;
	while (input->c <= input->width && len)
	{
		ft_putchar(input->line[x]);
		if (input->line[x + 1] == '\n')
		{
			if (!((get_curs_col() - 1) % input->col)
				&& input->line[x] != '\n')
				ft_putchar('\n');
			x2 = 0;
		}
		x2++;
		x++;
		input->c++;
		len--;
	}
	if ((get_curs_col() - 1) == input->col)
		ft_putchar('\n');
}

t_input		*up_sub(t_init *in, t_input *input, char buf[7])
{
	if (input->flag && input->qt && input->dflag > 1)
		up_sub_qt(input);
	else if (!input->next)
		return (input);
	else
	{
		clear_last_input(input); //oshibka ochistki
		print_history(input->next, input->next->line, 0);
		input->next->row = get_curs_row();
		input->next->flag = 1;
		if (input->next->hdoc)
		{
			fill_input_params_hd(input->next);
			input->next->x = input->next->width;
		}
		if (!input->next->qt)
		{
			if ((input->next->x % input->next->col == 1)
				&& input->next->x == input->next->width)
				ft_putchar('\n');
			return_curstox(input->next);
		}
		else
		{
			if (input->next->quote) //why is it need?
				input->next->x_quote = get_curs_col();//why only x_quote? but x_dquote?
			else if (input->next->dquote)
				input->next->x_dquote = get_curs_col();
			input->y = get_curs_row();
			input->next->dflag = input->next->sub_qt;
			input->next->save_x = input->next->x;
		}
		return (input->next);
	}
	return (input);
}

t_input		*down_sub(t_init *in, t_input *input, char buf[7])
{
	if (input->flag && input->qt && input->dflag < input->sub_qt)
		down_sub_qt(input);
	else if (!input->prev)
		return (input);
	else
	{
		clear_last_input(input);
		if (input->prev->quote && !input->prev->flag)
			print_history(input->prev, input->prev->line
				+ (input->prev->width - input->prev->width_quote), 1);
		else if (input->prev->dquote && !input->prev->flag)
			print_history(input->prev, input->prev->line
				+ (input->prev->width - input->prev->width_dquote), 1);
		else if (input->prev->qt)
			check_qt(input->prev);
		else
			print_history(input->prev, input->prev->line, 1);
		input->prev->row = get_curs_row();
		if (input->prev->prev)
			input->prev->flag = 1;
		if ((input->prev->x % input->prev->col == 1)
			&& input->prev->x == input->width)
			ft_putchar('\n');
		if (!input->prev->flag && !input->prev->qt)
		{
			return_curstox(input->prev);
			// input->prev->x = get_curs_col();
			// e++;
			// if (e > 0)
			// {
			// 	ft_printf("!%d %d!", input->prev->width, input->prev->x);
			// 	while (1);
			// }
			input->prev->y = get_curs_row();
		}
		else if (!input->prev->flag && input->prev->qt)
		{
			return_curstox_qt(input->prev);
			// input->prev->x = get_curs_col();
			input->prev->y = get_curs_row();
		}
		else if (input->prev->flag)
		{
			input->prev->x_quote = get_curs_col();
			if (input->prev->qt)
				input->prev->x = input->prev->save_x;
			else
				return_curstox(input->prev);
			input->y = get_curs_row();
			input->prev->dflag = input->prev->sub_qt;
		}
		return (input->prev);
	}
	return (input);
}
