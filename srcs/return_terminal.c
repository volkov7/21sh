/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return_terminal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 10:44:53 by nriker            #+#    #+#             */
/*   Updated: 2020/08/01 21:44:45 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		return_terminal(t_init *in)
{
	if (tcsetattr(0, TCSANOW, &in->old_tr) == -1)
		ft_error();
}
