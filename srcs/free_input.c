/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/01 19:13:09 by nriker            #+#    #+#             */
/*   Updated: 2020/08/01 19:13:27 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		free_input(t_input *input)
{
	if (input)
	{
		while (input->prev)
			input = input->prev;
		while (input->next)
		{
			if (input->line)
				free(input->line);
			if (input->ctrl_d_line)
				free(input->ctrl_d_line);
			if (input->word)
				free(input->word);
			input = input->next;
			if (input->prev)
				free(input->prev);
		}
		if (input->line)
			free(input->line);
		if (input->word)
			free(input->word);
		free(input);
	}
}
