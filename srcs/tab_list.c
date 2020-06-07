/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 12:46:14 by nriker            #+#    #+#             */
/*   Updated: 2020/03/15 13:22:54 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		tab_list(t_input *input, char **buf)
{
	t_column	*cl;

	get_curs_pos_inend(input);
	ft_putchar('\n');
	create_column(&cl);
	print_column(buf, cl);
	print_suggestion(input);
	// ft_putstr("21sh%> ");
	// ft_putstr(input->line);
	input->c = input->width;
	input->row = get_curs_row();
	// while (input->c != input->x)
	// {
	// 	if (input->c % input->col == 1)
	// 	{
	// 		ft_putstr("\e[1A");
	// 		ft_printf("\e[%dG", input->col);
	// 	}
	// 	else
	// 		ft_putstr("\e[1D");
	// 	input->c--;
	// }
	input->y = get_curs_row();
	free_buf(buf);
	free(cl);
}