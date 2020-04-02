#include "lexer.h"

void	remove_quote(char **str, size_t *i, size_t *rep)
{
	(*i)++;
	while ((*str)[*i] != '\0' && (*str)[*i] != '\'')
	{
		(*str)[*rep] = (*str)[*i];
		(*i)++;
		(*rep)++;
	}
	if ((*str)[*i] == '\'')
		(*i)++;
}

void	remove_backslash(char **str, size_t *i, size_t *rep)
{
	(*i)++;
	if ((*str)[*i] != '\0')
	{
		(*str)[*rep] = (*str)[*i];
		(*i)++;
		(*rep)++;
	}
}

void	remove_dquote(char **str, size_t *i, size_t *rep)
{
	(*i)++;
	while ((*str)[*i] != '\0' && (*str)[*i] != '"')
	{
		if ((*str)[*i] == '\\' && dquote_spec((*str)[*i + 1]) == 1)
			remove_backslash(str, i, rep);
		else
		{
			(*str)[*rep] = (*str)[*i];
			(*i)++;
			(*rep)++;
		}
	}
	if ((*str)[*i] == '"')
		(*i)++;
}

void	quote_removal(char **str)
{
	size_t	i;
	size_t	rep;

	i = 0;
	rep = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '\\')
			remove_backslash(str, &i, &rep);
		else if ((*str)[i] == '\'')
			remove_quote(str, &i, &rep);
		else if ((*str)[i] == '"')
			remove_dquote(str, &i, &rep);
		else
		{
			(*str)[rep] = (*str)[i];
			i++;
			rep++;
		}
	}
	ft_bzero(&((*str)[rep]), i - rep);
}

int		handle_expansions(t_ast *node, t_envlist *envlst)
{
	if (node == NULL)
		return (FUNC_FAIL);
	if (handle_expansions(node->right, envlst) == FUNC_ERROR)
		return (FUNC_ERROR);
	if (handle_expansions(node->left, envlst) == FUNC_ERROR)
		return (FUNC_ERROR);
	if (node->type == WORD && node->flags & HAS_SPECIAL)
	{
		if (search_spec(node, envlst) == FUNC_ERROR)
			return (FUNC_ERROR);
	}
	if (node->type == WORD)
		quote_removal(&node->str);
	return (FUNC_SUCCESS);
}
