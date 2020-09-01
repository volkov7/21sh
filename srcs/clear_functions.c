/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 12:09:03 by jsance            #+#    #+#             */
/*   Updated: 2020/08/02 12:10:44 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void			clear_tokenlst(t_tokenlst **tokenlst)
{
	t_tokenlst	*del;

	while (*tokenlst != NULL)
	{
		del = *tokenlst;
		*tokenlst = (*tokenlst)->next;
		ft_strdel(&del->str);
		free(del);
	}
}

void			delete_tree(t_ast **ast)
{
	if (*ast == NULL)
		return ;
	delete_tree(&(*ast)->left);
	delete_tree(&(*ast)->right);
	ft_strdel(&(*ast)->str);
	free(*ast);
}
