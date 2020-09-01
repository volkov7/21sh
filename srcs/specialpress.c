/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specialpress.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 20:33:38 by nriker            #+#    #+#             */
/*   Updated: 2020/08/09 13:53:24 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

int			speciallpress_check(t_input *input, char buf[7])
{
	if (buf[0] == 21 && !buf[1] && !buf[2] && !buf[3])
		pressed_second_word(input);
	else if (buf[0] == 18 && !buf[1] && !buf[2] && !buf[3])
		pressed_start_string(input);
	else if (buf[0] == 20 && !buf[1] && !buf[2] && !buf[3])
		pressed_end_string(input);
	else if (buf[0] == 9 && !buf[1] && !buf[2] && !buf[3])
		press_tab(input);
	return (1);
}

int			specialpress(t_input *input, char buf[7])
{
	if (buf[0] == 2 && !buf[1] && !buf[2] && !buf[3])
		pressed_home(input);
	else if (buf[0] == 14 && !buf[1] && !buf[2] && !buf[3])
		pressed_end(input);
	else if (buf[0] == 1 && !buf[1] && !buf[2] && !buf[3])
		pressed_prev_word(input);
	return (speciallpress_check(input, buf));
}
