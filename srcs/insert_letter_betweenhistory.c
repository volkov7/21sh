/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_letter_betweenhistory.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 09:08:46 by nriker            #+#    #+#             */
/*   Updated: 2020/08/08 09:13:23 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		insert_letter_betweenhistory(t_input *input, char buf[7])
{
	input->y = get_curs_row();
	ft_putchar(buf[0]);
	insert_print_string(input);
	input->row = get_curs_row();
	if (!(input->width % input->col) && input->row == input->li)
	{
		ft_putchar('\n');
		input->y--;
	}
	else if (!((input->x) % input->col))
		input->y++;
	input->row = get_curs_row();
	ft_printf("\e[%d;%dH", input->y, (input->x % input->col) + 1);
}
