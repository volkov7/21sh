/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_qt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 12:02:31 by nriker            #+#    #+#             */
/*   Updated: 2020/08/05 20:24:48 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		check_qt_cycle(t_input *input, int *x2, int *x)
{
	if (input->line[(*x) + 1] == '\n')
	{
		if (!((get_curs_col() - 1) % input->col)
			&& input->line[(*x)] != '\n')
			ft_putchar('\n');
		(*x2) = 0;
	}
}

void		check_qt(t_input *input)
{
	int	x;
	int	x2;
	int	len;

	len = ft_strlen(input->line) - 1;
	x = 0;
	x2 = 7;
	input->c = 8;
	while (input->c <= input->width && len)
	{
		ft_putchar(input->line[x]);
		check_qt_cycle(input, &x2, &x);
		x2++;
		x++;
		input->c++;
		len--;
	}
	if ((get_curs_col() - 1) == input->col)
		ft_putchar('\n');
}
