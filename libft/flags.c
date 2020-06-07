/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 13:49:59 by nriker            #+#    #+#             */
/*   Updated: 2019/11/03 15:48:58 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		check_alone(t_flags *fl)
{
	if (fl->type == 'm')
	{
		check_fd(fl);
		return (1);
	}
	if (fl->type == 'f')
	{
		check_float(fl);
		return (1);
	}
	if (fl->len_rev_s == 1 || fl->type == 0)
	{
		if (!(fl->tmp = flags_zero(fl)))
			return (1);
		return (1);
	}
	return (0);
}

int				flags(t_flags *fl)
{
	if (check_alone(fl))
		return (0);
	if (fl->type == '%')
		fl->tmp = ft_strdup("%");
	else if ((!fl->lsize && !fl->hsize && fl->type != 'p') || fl->type == 'r')
	{
		if (!(fl->tmp = flags_zero(fl)))
			return (0);
	}
	else if (!(fl->tmp = flags_size(fl)))
		return (-1);
	if (fl->found_dot && fl->type != '%' && fl->fprecision >= 0)
		if (!(fl->tmp = flags_precision(fl)))
			return (0);
	fl->tmp = check_width(fl->right_s, fl->tmp, fl);
	return (fl->len_rev_s);
}
