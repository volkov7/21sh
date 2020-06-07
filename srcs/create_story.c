/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_story.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:23:51 by nriker            #+#    #+#             */
/*   Updated: 2020/02/07 15:17:06 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_story		*create_story()
{
	t_story		*story;

	if (!(story = (t_story*)malloc(sizeof(t_story))))
		ft_error_select(3);
	story->quotes = 0;
	story->next = 0;
	story->line = 0;
	return (story);
}
