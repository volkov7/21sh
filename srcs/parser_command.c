/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 15:06:08 by jsance            #+#    #+#             */
/*   Updated: 2020/07/06 15:06:09 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		parser_cmd_prefix(t_tokenlst **token_lst, t_ast **prefix,
							t_ast **last_prefix)
{
	t_ast	*new_prefix;

	new_prefix = NULL;
	if (TOKEN_TYPE == IO_NUMBER || is_redirect(TOKEN_TYPE))
	{
		if (parser_io_redirect(token_lst, &new_prefix) == FUNC_FAIL)
			return (return_ast_del(&new_prefix));
		if (*prefix == NULL)
			*prefix = new_prefix;
		else
			(*last_prefix)->left = new_prefix;
		*last_prefix = new_prefix;
		if (parser_cmd_prefix(token_lst, prefix, last_prefix) == FUNC_FAIL)
			return (FUNC_FAIL);
	}
	return (FUNC_SUCCESS);
}

int		parser_cmd_word(t_tokenlst **token_lst, t_ast **ast, t_ast **prefix)
{
	if (TOKEN_TYPE == WORD)
	{
		if (ast_addnode(token_lst, ast) == FUNC_ERROR)
			return (return_ast_del(ast));
		(*ast)->right = *prefix;
		return (FUNC_SUCCESS);
	}
	else if (*prefix != NULL)
	{
		*ast = *prefix;
		return (FUNC_SUCCESS);
	}
	return (FUNC_FAIL);
}

int		parser_cmd_arg(t_tokenlst **token_lst, t_ast **ast,
				t_ast **last_cmd_arg, t_ast **last_prefix)
{
	t_ast	*new_node;

	new_node = NULL;
	if (ast_addnode(token_lst, &new_node) == FUNC_FAIL)
		return (FUNC_FAIL);
	if (*last_cmd_arg == NULL)
		(*ast)->left = new_node;
	else
		(*last_cmd_arg)->left = new_node;
	*last_cmd_arg = new_node;
	if (!parser_cmd_sufix(token_lst, ast, last_cmd_arg, last_prefix))
		return (FUNC_FAIL);
	return (FUNC_SUCCESS);
}

/*
**	Parser_command does three things
**	It looks for redir tokens and they are set to prefix
**	If there is a command, the prefix is added to the right of command
**	If there is no command just return prefix
**	Command arguments adding below command
**	Any redirections are added to the end of prefix
*/

int		parser_command(t_tokenlst **token_lst, t_ast **ast)
{
	t_ast	*prefix;
	t_ast	*last_prefix;
	t_ast	*last_cmd_arg;

	prefix = NULL;
	last_prefix = NULL;
	last_cmd_arg = NULL;
	if (TOKEN_TYPE == WORD || TOKEN_TYPE == IO_NUMBER
							|| is_redirect(TOKEN_TYPE))
	{
		if (parser_cmd_prefix(token_lst, &prefix, &last_prefix) == FUNC_FAIL)
			return (FUNC_FAIL);
		if (parser_cmd_word(token_lst, ast, &prefix) == FUNC_FAIL)
			return (return_ast_del(ast));
		if (!parser_cmd_sufix(token_lst, ast, &last_cmd_arg, &last_prefix))
			return (return_ast_del(ast));
		return (FUNC_SUCCESS);
	}
	return (FUNC_FAIL);
}
