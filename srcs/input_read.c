/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_read.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 12:31:34 by nriker            #+#    #+#             */
/*   Updated: 2020/08/08 16:26:39 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_input		*read_input(t_init *in, t_input *input)
{
	char		buf[7];

	ft_bzero((void*)buf, 7);
	while (1)
	{
		if (read(0, buf, 7) == -1)
			ft_error();
		input = get_input(0);
		if ((buf[0] == 13 || buf[0] == 10) && !buf[1]
			&& input->flag && check_flag_qt(input))
			input = insert_history_line(input);
		if (buf[0] == 27 && buf[1] == 91 && (buf[2] == 65 || buf[2] == 66
				|| buf[2] == 67 || buf[2] == 68))
		{
			input = arrowpress(input, buf);
			get_input(input);
		}
		else if (!letterpress(in, input, buf) || !delete_press(input, buf)
			|| !specialpress(input, buf) || !enter_press(input, buf))
			return (input);
		ft_bzero((void*)buf, 7);
	}
	return (input);
}
