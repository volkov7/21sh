#include "lexer.h"

int		is_redirect(t_tokens type)
{
	if (type == DLESS || type == DGREAT || type == LESS ||
			type == GREAT || type == LESSAND || type == GREATAND)
		return (1);
	return (0);
}

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

int		add_right_node(t_tokenlst **token_lst, t_ast **ast,
					int (*parser_func)(t_tokenlst **, t_ast **))
{
	t_ast	*right_node;

	right_node = NULL;
	if (parser_func(token_lst, &right_node) == FUNC_FAIL)
		return (return_ast_del(ast));
	(*ast)->right = right_node;
	return(FUNC_SUCCESS);
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
	if (TOKEN_TYPE == WORD || TOKEN_TYPE == IO_NUMBER || is_redirect(TOKEN_TYPE))
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

/*
**	After parser_command, we can have a PIPE token
**	PIPE token is adding to the ast
**	Previous ast adding left below PIPE
**	calling parser_command and result ast put in right node below PIPE
*/

int		parser_pipe_sequence(t_tokenlst **token_lst, t_ast **ast)
{
	if (parser_command(token_lst, ast) == FUNC_SUCCESS)
	{
		while (TOKEN_TYPE == PIPE)
		{
			if (ast_addnode(token_lst, ast) == FUNC_FAIL)
				return(return_ast_del(ast));
			if (add_right_node(token_lst, ast, &parser_command) == FUNC_FAIL)
				return (FUNC_FAIL);
		}
		return (FUNC_SUCCESS);
	}
	return (FUNC_FAIL);
}

/*
**	After parser_pipe_sequence, we can have an AND_IF or OR_IF token
**	In that case the current token is adding to the ast
**	previous ast adding to left node below AND_IF or OR_IF token
**	calling parser_pipe_sequence and result put in right node below AND_IF or OR_IF token
*/

int		parser_and_or(t_tokenlst **token_lst, t_ast **ast)
{
	if (parser_pipe_sequence(token_lst, ast) == FUNC_SUCCESS)
	{
		while (TOKEN_TYPE == AND_IF || TOKEN_TYPE == OR_IF)
		{
			if (ast_addnode(token_lst, ast) == FUNC_FAIL)
				return(return_ast_del(ast));
			if (!add_right_node(token_lst, ast, &parser_pipe_sequence))
				return (FUNC_FAIL);
		}
		return (FUNC_SUCCESS);
	}
	return (FUNC_FAIL);
}

/*
**	After parser_and_or is done, we can have SEMICOL token
**	In that case the current token is adding to the ast
**	previous ast adding to left node below SEMICOL token
**	calling parser_and_or and result put in right node below SEMICOL token
*/

int		parser_list(t_tokenlst **token_lst, t_ast **ast)
{
	if (parser_and_or(token_lst, ast) == FUNC_SUCCESS)
	{
		if (TOKEN_TYPE == SEMICOL)
		{
			if (ast_addnode(token_lst, ast) == FUNC_FAIL)
				return(return_ast_del(ast));
			if (TOKEN_TYPE != NEWLINE && TOKEN_TYPE != END)
			{
				if (add_right_node(token_lst, ast, &parser_list) == FUNC_FAIL)
					return (FUNC_FAIL);
			}
		}
		return (FUNC_SUCCESS);
	}
	return (FUNC_FAIL);
}

int		parser_complete_command(t_tokenlst **token_lst, t_ast **ast)
{
	if (parser_list(token_lst, ast) == FUNC_FAIL || (TOKEN_TYPE != NEWLINE &&
													TOKEN_TYPE != END))
		return(return_ast_del(ast));
	return(FUNC_SUCCESS);
}

int		parser_start(t_tokenlst **token_lst, t_ast **ast)
{
	t_tokenlst	*tmp;

	tmp = (*token_lst)->next;
	if (parser_complete_command(&tmp, ast) != FUNC_SUCCESS)
	{
		ft_putstr("Syntax error!\n");
		return (FUNC_FAIL);
	}
	return (FUNC_SUCCESS);
}