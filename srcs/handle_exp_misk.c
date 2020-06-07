#include "lexer.h"

int		dquote_spec(char c)
{
	if (c == '$' || c == '`' || c == '\\' || c == '\n' || c == '"')
		return (FUNC_SUCCESS);
	return (FUNC_FAIL);
}

void	remove_heredoc_baskslash(char **str, size_t *i, size_t *rep)
{
	if (dquote_spec((*str)[*i + 1]) == FUNC_SUCCESS)
		remove_backslash(str, i, rep);
	else
	{
		(*str)[*rep] = (*str)[*i];
		(*i)++;
		(*rep)++;
	}
}