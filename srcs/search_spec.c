/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_spec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 15:07:26 by jsance            #+#    #+#             */
/*   Updated: 2020/07/06 15:07:27 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	update_quote(char *quote, char c, size_t *i)
{
	if (*quote == 0x0)
		*quote = c;
	else if (*quote == c)
		*quote = 0x0;
	(*i)++;
}

int		search_spec(t_ast *node, t_envlist *envlst)
{
	char	quote;
	size_t	i;

	i = 0;
	quote = 0x0;
	while (node->str[i] != '\0')
	{
		if (node->str[i] == '\\' && quote != '\'')
			i += 2;
		else if (node->str[i] == '\'' || node->str[i] == '\"')
			update_quote(&quote, node->str[i], &i);
		else if (node->str[i] == '$' && quote != '\'')
		{
			if (dollar_expansion(&node->str, &i, envlst) == FUNC_ERROR)
				return (FUNC_ERROR);
		}
		else if (node->str[i] == '~')
		{
			if (tilde_expansion(node, &i, envlst) == FUNC_ERROR)
				return (FUNC_ERROR);
		}
		else
			i++;
	}
	return (FUNC_SUCCESS);
}
