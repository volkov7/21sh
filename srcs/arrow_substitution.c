/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrow_substitution.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:13:28 by nriker            #+#    #+#             */
/*   Updated: 2020/08/08 16:43:29 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		print_last_input_qt(t_input *input)
{
	if (input->quote)
		ft_printf("\e[%d;%dH", input->c - input->qlines_in_com + 1, input->c2);
	else if (input->dquote)
		ft_printf("\e[%d;%dH", input->c - input->dqlines_in_com + 1, input->c2);
}

void		clear_last_input(t_input *i)
{
	get_curs_pos_inend(i);
	i->c = get_curs_row();
	i->c2 = i->index;
	if (!i->flag && i->qt)
	{
		if (i->quote)
		{
			ft_printf("\e[%d;%dH", i->c - i->qlines_in_com + 1, i->c2);
		}
		else if (i->dquote)
			ft_printf("\e[%d;%dH", i->c - i->dqlines_in_com + 1, i->c2 + 1);
	}
	else
	{
		ft_printf("\e[%d;%dH", i->c - i->lines_in_com + 1, i->c2);
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

t_input		*up_sub(t_input *input)
{
	if (input->flag && input->qt && input->dflag > 1)
		up_sub_qt(input);
	else if (!input->next || (!input->flag && input->qt)
				|| input->heredok)
		return (input);
	else
		return (arrow_substitution_up(input));
	return (input);
}

t_input		*down_sub(t_input *input)
{
	if (input->flag && input->qt && input->dflag < input->sub_qt)
		down_sub_qt(input);
	else if (!input->prev || (!input->flag && input->qt)
				|| input->heredok)
		return (input);
	else
		return (arrow_substitution_down(input));
	return (input);
}
