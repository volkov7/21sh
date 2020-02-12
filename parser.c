#include "lexer.h"

int		parser_cmd_prefix(t_tokenlst *token_lst, t_ast **ast)
{
	return (FUNC_FAIL);
}

int		parser_cmd_word(t_tokenlst *token_lst, t_ast **ast)
{
	return (FUNC_FAIL);
}

int		parser_cmd_sufix(t_tokenlst *token_lst, t_ast **ast)
{
	return (FUNC_FAIL);
}

int		parser_command(t_tokenlst *token_lst, t_ast **ast)
{
	t_ast	*prefix;
	t_ast	*last_prefix;
	t_ast	*last_cmd_arg;

	prefix = NULL;
	last_prefix = NULL;
	last_cmd_arg = NULL;
}

int		parser_pipe_sequence(t_tokenlst *token_lst, t_ast **ast)
{
	parser_command(token_lst, ast);
}

int		parser_and_or(t_tokenlst *token_lst, t_ast **ast)
{
	parser_pipe_sequence(token_lst, ast);
}

int		parser_list(t_tokenlst *token_lst, t_ast **ast)
{
	parser_and_or(token_lst, ast);
}

int		parser_complete_command(t_tokenlst *token_lst, t_ast **ast)
{
	parser_list(token_lst, ast);
}

int		parser_start(t_tokenlst *token_lst, t_ast **ast)
{
	t_tokenlst	*tmp;

	tmp = token_lst->next;
	parser_complete_command(tmp, ast);
}