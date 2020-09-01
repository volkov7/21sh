/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_size_of_window.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 07:05:44 by nriker            #+#    #+#             */
/*   Updated: 2020/08/02 07:07:13 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void					change_size_of_window(t_input *input)
{
	struct winsize	w;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	input->col = w.ws_col;
	input->li = w.ws_row;
}
