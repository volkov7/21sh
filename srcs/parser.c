#include "lexer.h"

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
**	After parser_pipe_sequence, we can have an AND_IF or OR_IF tokens
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

/*
**	Skip START token
*/

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