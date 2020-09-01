/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_story.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:23:51 by nriker            #+#    #+#             */
/*   Updated: 2020/08/02 10:23:06 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

t_story		*create_story(void)
{
	t_story		*story;

	if (!(story = (t_story*)malloc(sizeof(t_story))))
		ft_error_select(3);
	story->quotes = 0;
	story->next = 0;
	story->line = 0;
	return (story);
}
