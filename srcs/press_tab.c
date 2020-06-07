/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_tab.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 11:09:45 by nriker            #+#    #+#             */
/*   Updated: 2020/05/17 03:02:57 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void			print_suggestion_q(t_input *input)
{

}

void			print_suggestion_hd(t_input *input)
{
	if (input->hdoc == 1)
	{
		ft_putstr("> ");
	}
	else if (input->hdoc == 2)
	{
		ft_putstr("heredoc> ");
	}
	ft_putstr(input->line);
	if ((ft_strlen(input->line) + (input->index - 1)) == input->col)
	{
		ft_putchar('\n');
		input->lines_in_com++;
	}
	return_curstox(input);
}

void			print_suggestion(t_input *input)
{
	if (input->hdoc && !input->qt)
		print_suggestion_hd(input);
	else if (!input->qt)
	{
		ft_putstr("21sh%> ");
		ft_putstr(input->line);
		if ((ft_strlen(input->line) + (input->index - 1)) == input->col)
		{
			ft_putchar('\n');
			input->lines_in_com++;
		}
		return_curstox(input);
	}
	else if (input->quote)
	{
		ft_putstr("quote> ");
		ft_putstr(input->line + (input->width - input->width_quote));
		if ((ft_strlen(input->line + (input->width - input->width_quote)) + (input->index - 1)) == input->col)
		{
			ft_putchar('\n');
			// input->lines_in_com++;
			input->lines_in_qt++;
			input->qlines_in_com++;
		}
		return_curstox_qt(input);
	}
	else if (input->dquote)
	{
		ft_putstr("dquote> ");
		ft_putstr(input->line + (input->width - input->width_dquote + 1));
		if ((ft_strlen(input->line + (input->width - input->width_dquote + 1)) + input->index) == input->col)
		{
			ft_putchar('\n');
			// input->lines_in_com++;
			input->qlines_in_com++;
			input->lines_in_qt++;
		}
		return_curstox_qt(input);
	}
}

void			check_big_list(t_input *input, char **buf)
{
	char		b[7];

	if (input->list_size > 20)
	{
		get_curs_pos_inend(input);
		ft_bzero((void*)b, 7);
		ft_printf("\nDisplay all %d possibilities? (y or n)", input->list_size);
		if (read(0, b, 7) == -1)
			ft_error();
		if (b[0] == 'y' || (b[0] == 9)
			|| ((b[0] == 13 || b[0] == 10 || b[0] == 121) && !b[1]))
		{
			tab_list(input, buf);
		}
		else
		{
			ft_putchar('\n');
			print_suggestion(input);
			free_buf(buf);
		}
	}
	else
		tab_list(input, buf);
}

void			press_tab(t_init *in, t_input *input)
{
	char **buf;

	input->word = get_partword(input);
	if (check_firstword(input)
		&& (!input->flag) && !input->exec_firstword)
		buf = get_buf_path(input);
	else
		buf = get_buf21sh(input);
	input->exec_firstword = 0;
	if (input->list_size == 1)
	{
		if (!input->qt)
			tab_insert_word(input, buf);
		else
			tab_insert_word_q(input, buf);
		free_buf(buf);
	}	
	else if (input->list_size)
		check_big_list(input, buf);
	if (input->word)
		free(input->word);
	input->word = 0;
	input->list_size = 0;
}
