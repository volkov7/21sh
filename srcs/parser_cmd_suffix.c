#include "lexer.h"

/*
** ast always will be NULL in this func. Create io_redirect tree
*/

int		parser_io_redirect(t_tokenlst **token_lst, t_ast **ast)
{
	t_ast	*filename;

	filename = NULL;
	if (TOKEN_TYPE == IO_NUMBER && ast_addnode(token_lst, ast) == FUNC_FAIL)
		return (FUNC_FAIL);
	if (is_redirect(TOKEN_TYPE) == 0 || ast_addnode(token_lst, ast) == FUNC_FAIL)
		return (return_ast_del(ast));
	if (TOKEN_TYPE != WORD || ast_addnode(token_lst, &filename) == FUNC_FAIL)
		return (return_ast_del(ast));
	if ((*ast)->left == NULL)
		(*ast)->left = filename;
	else
		(*ast)->left->left = filename;
	(*ast)->right = (*ast)->left;
	(*ast)->left = NULL;
	return(FUNC_SUCCESS);
}

int		parser_cmd_sufix(t_tokenlst **token_lst, t_ast **ast,
				t_ast **last_cmd_arg, t_ast **last_prefix)
{
	t_ast	*new_node;

	new_node = NULL;
	if (TOKEN_TYPE == IO_NUMBER || is_redirect(TOKEN_TYPE))
	{
		if (parser_io_redirect(token_lst, &new_node) == FUNC_FAIL)
			return (FUNC_FAIL);
		if ((*ast)->right == NULL)
			(*ast)->right = new_node;
		else
			(*last_prefix)->left = new_node;
		*last_prefix = new_node;
		if (!parser_cmd_sufix(token_lst, ast, last_cmd_arg, last_prefix))
			return (FUNC_FAIL);
	}
	else if (TOKEN_TYPE == WORD)
	{
		if (!parser_cmd_arg(token_lst, ast, last_cmd_arg, last_prefix))
			return (FUNC_FAIL);
	}
	return (FUNC_SUCCESS);
}
