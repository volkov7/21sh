#include "lexer.h"

int		dquote_spec(char c)
{
	if (c == '$' || c == '`' || c == '\\' || c == '\n' || c == '"')
		return (1);
	return (0);
}
