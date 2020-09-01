/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrowpress.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 20:19:40 by nriker            #+#    #+#             */
/*   Updated: 2020/08/05 20:46:16 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_input		*arrowpress(t_input *input, char buf[7])
{
	if (buf[0] == 27 && buf[1] == 91 && buf[2] == 68)
		press_left(input);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 67)
		press_right(input);
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 65)
		return (up_sub(input));
	else if (buf[0] == 27 && buf[1] == 91 && buf[2] == 66)
		return (down_sub(input));
	return (input);
}
