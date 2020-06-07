/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_select.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 12:57:28 by nriker            #+#    #+#             */
/*   Updated: 2020/02/05 12:53:38 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void	ft_error_select(int x)
{
	ft_putstr_fd("21sh: ", 2);
	if (x == 1)
		ft_putstr_fd("too much arguments\n", 2);
	else if (x == 2)
		ft_putstr_fd("variable TERM not exist\n", 2);
	else if (x == 3)
		ft_putstr_fd("error in memory allocation\n", 2);
	exit(EXIT_FAILURE);
}
