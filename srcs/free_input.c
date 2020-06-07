/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/03 16:30:45 by nriker            #+#    #+#             */
/*   Updated: 2020/02/13 10:27:59 by nriker           ###   ########.fr       */
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