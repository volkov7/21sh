/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pressed_delete.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 13:50:47 by nriker            #+#    #+#             */
/*   Updated: 2020/02/03 14:46:47 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static void	delete_elem_list(t_init **in)
{
	t_elem	**copy;

	copy = &((*in)->el);
	while (!(*copy)->cursor)
		(*copy) = (*copy)->next;
	free_elem_struct(copy, in);
}

static void	free_list(t_init *in)
{
	int		i;

	i = -1;
	if (in->list)
	{
		while (in->list[++i])
			free(in->list[i]);
		free(in->list);
	}
}

void		pressed_delete(t_init *in)
{
	t_elem	*copy;
	int		i;
	char	**new_list;

	in->call++;
	if (in->nb == 1)
		pressed_esk(in);
	delete_elem_list(&in);
	in->nb--;
	new_list = (char**)malloc(sizeof(char*) * in->nb + 1);
	new_list[in->nb] = 0;
	i = -1;
	copy = in->el;
	while (copy)
	{
		new_list[++i] = ft_strdup(copy->word);
		copy = copy->next;
	}
	in->call = 1;
	copy = in->el;
	i = -1;
	free_list(in);
	in->list = new_list;
	print_list(in);
}
