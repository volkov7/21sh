/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 15:48:57 by nriker            #+#    #+#             */
/*   Updated: 2020/05/17 04:13:07 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_input		*create_input()
{
	t_input		*input;

	if (!(input = (t_input*)malloc(sizeof(t_input))))
		ft_error_select(3);
	input->flag = 0;
	input->dflag = 1;
	input->word = 0;
	input->list_size = 0;
	input->tab_row = 0;
	input->p_tab = 0;
	input->p_tab_part = 0;
	input->c = 0;
	input->c2 = 0;
	input->quote = 0;
	input->dquote = 0;
	input->qt = 0;
	input->x_quote = 0;
	input->width_quote = 0;
	input->x_dquote = 0;
	input->width_dquote = 0;
	input->line = 0;
	input->width = 8;
	// input->len = 7;
	// input->len_x = 7;
	input->line = 0;
	input->x =  8;
	input->col = tgetnum("co");
	input->li = tgetnum("li");
	input->y = get_curs_row();
	input->row = input->y;
	// ft_printf("%d", input->row);
	input->old_row = 0;
	input->old = 0;
	input->o = 0;
	input->f = 0;
	input->lines_in_com = 1;
	input->lines_in_qt = 1;
	input->qlines_in_com = 1;
	input->dqlines_in_com = 1;
	// input->qt_str = 1;
	input->next = 0;
	input->prev = 0;
	input->sub_qt = 1;
	input->save_x = 10;
	input->flag_qt = 0;
	input->sx = 0;//
	input->sy = 0;//
	input->path_dirs = 0;
	input->exec_firstword = 0;
	input->hdoc = 0;
	input->index = 8;
	// input->x_hdoc = 0;
	// input->width_hdoc = 0;
	// input->lines_in_hdoc = 1;
	return (input);
}