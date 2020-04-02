#include "lexer.h"

t_tokenlst		*new_token_lst(int flags, char *str, t_tokens type)
{
	t_tokenlst	*fresh;

	fresh = (t_tokenlst*)malloc(sizeof(t_tokenlst));
	if (fresh == NULL)
		return (NULL);
	ft_memset((void*)fresh, 0, sizeof(t_tokenlst));
	fresh->flags = flags;
	fresh->str = str;
	fresh->type = type;
	fresh->next = NULL;
	return (fresh);
}

int				tokenlst_addback(t_tokenlst **token_lst, int flags, char *str,
																t_tokens type)
{
	if (*token_lst == NULL)
	{
		if ((*token_lst = new_token_lst(flags, str, type)) == NULL)
			return (FUNC_ERROR);
		return (FUNC_SUCCESS);
	}
	else
		return (tokenlst_addback(&(*token_lst)->next, flags, str, type));
}

int				is_spec(char c)
{
	if (c != '\0' && ft_strchr("-~$?/\\'\"", c) != NULL)
		return (1);
	return (0);
}

int		ft_isblank(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}
