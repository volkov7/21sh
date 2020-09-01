/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expansions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 15:11:46 by jsance            #+#    #+#             */
/*   Updated: 2020/07/12 19:40:11 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if ((*str)[*i] == '\\' && dquote_spec((*str)[*i + 1]) == FUNC_SUCCESS)
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

void	quote_removal(char **str, int is_heredoc)
{
	size_t	i;
	size_t	rep;

	i = 0;
	rep = 0;
	while ((*str)[i] != '\0')
	{
		if ((*str)[i] == '\\' && is_heredoc == 0)
			remove_backslash(str, &i, &rep);
		else if ((*str)[i] == '\\' && is_heredoc)
			remove_heredoc_baskslash(str, &i, &rep);
		else if ((*str)[i] == '\'' && is_heredoc == 0)
			remove_quote(str, &i, &rep);
		else if ((*str)[i] == '"' && is_heredoc == 0)
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
	if (node->type == WORD && node->flags & HAS_SPECIAL
		&& !(node->flags & HEREDOC_NOEXP))
	{
		if (search_spec(node, envlst) == FUNC_ERROR)
			return (FUNC_ERROR);
	}
	if (node->type == WORD && !(node->flags & HEREDOC_NOEXP))
		quote_removal(&node->str, node->flags & IS_HEREDOC);
	return (FUNC_SUCCESS);
}
