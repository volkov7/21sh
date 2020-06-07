/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copylastinput.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/07 18:31:52 by nriker            #+#    #+#             */
/*   Updated: 2020/02/07 18:46:26 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_input			*copylastinput(t_input *copy)
{
	t_input		*input;

	input = create_input();
	if (copy)
	{
		input->line = copy->line;
		input->flag = copy->flag;
		input->x = copy->x;
		input->width = copy->width;
		input->quote = copy->quote;
		input->width_quote = copy->width_quote;
		input->x_quote = copy->x_quote;
		input->dquote = copy->dquote;
		input->width_dquote = copy->width_dquote;
		input->x_dquote = copy->x_dquote;
		return (input);
	}
	return (input);
}