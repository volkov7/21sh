/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_misk.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 15:01:06 by jsance            #+#    #+#             */
/*   Updated: 2020/07/06 15:01:07 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	ast_del(t_ast **ast)
{
	if (ast == NULL || *ast == NULL)
		return ;
	if ((*ast)->left != NULL)
		ast_del(&(*ast)->left);
	if ((*ast)->right != NULL)
		ast_del(&(*ast)->right);
	if ((*ast)->str)
		ft_strdel(&(*ast)->str);
	ft_memdel((void**)ast);
}

int		return_ast_del(t_ast **ast)
{
	ast_del(ast);
	return (FUNC_FAIL);
}

int		is_redirect(t_tokens type)
{
	if (type == DLESS || type == DGREAT || type == LESS ||
			type == GREAT || type == LESSAND || type == GREATAND)
		return (1);
	return (0);
}
