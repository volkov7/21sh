/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_press.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 21:43:47 by nriker            #+#    #+#             */
/*   Updated: 2020/08/01 21:43:48 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			delete_press(t_input *input, char buf[7])
{
	if ((buf[0] == 127 && !buf[1] && !buf[2]))
	{
		input->p_tab = 0;
		input->p_tab_part = 0;
		input->flag_qt = 0;
		if (input->flag && input->qt && input->x > input->index)
			delete_history_qt_between(input);
		else if (input->x > input->index && !input->qt)
			delete_letter(input);
		else if (input->x_quote > input->index && !input->flag)
			delete_quote(input);
		else if (input->x_dquote > 9 && !input->flag)
			delete_dquote(input);
	}
	return (1);
}
