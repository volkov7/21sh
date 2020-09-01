/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_envlst.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 06:06:03 by nriker            #+#    #+#             */
/*   Updated: 2020/08/02 06:06:04 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_envlist		*get_envlst(t_envlist *envlst)
{
	static t_envlist		*lst;

	if (!envlst)
		return (lst);
	else
		lst = envlst;
	return (0);
}
