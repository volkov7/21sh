#include "lexer.h"
#include <stdio.h>// Don't forget fix this file

#define COUNT 5

void		print_node(t_tokenlst *node)
{
	printf("%-16s", get_token_str(node->type));
	if (node->type == IO_NUMBER || node->type == WORD)
		printf("%-16s", node->str);
	else
		printf("%-16s", get_token_str(node->type));
	if (node->flags & HAS_SPECIAL)
		printf("<has_special>");
	printf("\n");
}

void		print_lex(t_tokenlst *token_lst)
{
	if (token_lst == NULL)
		return ;
	print_node(token_lst);
	print_lex(token_lst->next);
}

static char	*single_tk_str(t_tokens type)
{
	if (type == AND_IF)
		return ("&&");
	else if (type == OR_IF)
		return ("||");
	else if (type == DLESS)
		return ("<<");
	else if (type == DGREAT)
		return (">>");
	else if (type == LESS)
		return ("<");
	else if (type == GREAT)
		return (">");
	else if (type == LESSAND)
		return ("<&");
	else if (type == GREATAND)
		return (">&");
	else if (type == PIPE)
		return ("|");
	else if (type == SEMICOL)
		return (";");
	return ("ERROR");
}

char		*get_token_str(t_tokens type)
{
	if (type == START)
		return ("START");
	else if (type == WORD)
		return ("WORD");
	else if (type == IO_NUMBER)
		return ("IO_NUM");
	else if (type == NEWLINE)
		return ("\\n");
	else if (type == END)
		return ("END");
	else
		return (single_tk_str(type));
}

static void		print_color(int color)
{
	if (color == 0)
		printf("\e[0;31m");
	if (color == 1)
		printf("\e[0;32m");
	if (color == 2)
		printf("\e[0;33m");
	if (color == 3)
		printf("\e[0;34m");
	if (color == 4)
		printf("\e[0;35m");
	if (color == 5)
		printf("\e[0;36m");
	if (color == 6)
		printf("\e[0;37m");
}

void	print_tree(t_ast *ast, int space, int depth)
{
	int i;

	if (ast == NULL)
		return;
	space += COUNT;
	print_tree(ast->right, space, depth + 1);
	// ft_putstr("\n");
	for (i = COUNT; i < space; i++)
		ft_putchar(' ');
	print_color(depth % 7);
	if (ast->str != NULL)
		printf("%s\e[0m\n", ast->str);
	else
		printf("%s\e[0m\n", get_token_str(ast->type));
	print_tree(ast->left, space, depth + 1);
}
