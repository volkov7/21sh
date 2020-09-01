/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_node_work.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 15:48:45 by jsance            #+#    #+#             */
/*   Updated: 2020/08/02 10:24:28 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_ast	*create_new_node(t_tokenlst *token)
{
	t_ast	*new;

	if (!(new = (t_ast*)malloc(sizeof(t_ast))))
		return (NULL);
	new->flags = token->flags;
	new->type = token->type;
	if (token->str != NULL)
	{
		if (!(new->str = ft_strdup(token->str)))
			return (NULL);
	}
	else
		new->str = NULL;
	new->left = NULL;
	new->right = NULL;
	return (new);
}

int		ast_addnode(t_tokenlst **token_lst, t_ast **ast)
{
	t_ast *new;

	if (!(new = create_new_node(*token_lst)))
		return (FUNC_FAIL);
	new->left = *ast;
	*ast = new;
	(*token_lst) = (*token_lst)->next;
	return (FUNC_SUCCESS);
}

int		add_right_node(t_tokenlst **token_lst, t_ast **ast,
					int (*parser_func)(t_tokenlst **, t_ast **))
{
	t_ast	*right_node;

	right_node = NULL;
	if (parser_func(token_lst, &right_node) == FUNC_FAIL)
		return (return_ast_del(ast));
	(*ast)->right = right_node;
	return (FUNC_SUCCESS);
}
