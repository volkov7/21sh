/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 12:03:43 by jsance            #+#    #+#             */
/*   Updated: 2020/08/03 19:51:19 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"
#include "lexer.h"

int				add_token_to_lst(t_tokenlst *tokenlst, t_token *token)
{
	int		tk_start;
	char	*str;

	tk_start = token->str_index - token->tk_len;
	str = NULL;
	if (tk_start < 0)
		return (FUNC_ERROR);
	if (token->tk_type == WORD || token->tk_type == IO_NUMBER)
	{
		if (!(str = ft_strnew(token->tk_len)))
			return (FUNC_ERROR);
		if (!(ft_strncpy(str, &(token->str[tk_start]), token->tk_len)))
			return (FUNC_ERROR);
	}
	if (tokenlst_addback(&tokenlst, token->flags, str, token->tk_type) == -1)
		return (FUNC_ERROR);
	return (FUNC_SUCCESS);
}

void			clean_token(t_token *token)
{
	(*token).flags = 0;
	(*token).tk_len = 0;
	(*token).tk_type = ERROR;
}

int				lexer_scanner(char *input, t_tokenlst *token_lst)
{
	t_token	token;

	ft_bzero(&token, sizeof(t_token));
	token.str = input;
	while (ft_isblank(TOKEN_CHAR))
		(token.str_index)++;
	while (TOKEN_CHAR != '\0')
	{
		lexer_state_start(&token);
		if (add_token_to_lst(token_lst, &token) == FUNC_ERROR)
			return (FUNC_ERROR);
		clean_token(&token);
		while (ft_isblank(TOKEN_CHAR))
			(token.str_index)++;
	}
	return (FUNC_SUCCESS);
}

int				lexer(char **input, t_tokenlst **token_lst)
{
	if (tokenlst_addback(token_lst, 0, NULL, START) != FUNC_SUCCESS)
		return (FUNC_ERROR);
	if (lexer_scanner(*input, *token_lst) != FUNC_SUCCESS)
		return (FUNC_ERROR);
	if (tokenlst_addback(token_lst, 0, NULL, END) != FUNC_SUCCESS)
		return (FUNC_ERROR);
	return (FUNC_SUCCESS);
}

void			prepare_lexer(char *line, t_envlist **envlst, t_init *in,
															t_input *input)
{
	t_tokenlst	*tokenlst;
	t_ast		*ast;

	ast = NULL;
	tokenlst = NULL;
	if (lexer(&line, &tokenlst) != FUNC_SUCCESS
		|| here_doc(&tokenlst, in, input) != FUNC_SUCCESS
		|| parser_start(&tokenlst, &ast) != FUNC_SUCCESS)
	{
		clear_tokenlst(&tokenlst);
		return ;
	}
	return_terminal(in);
	exec_complete_command(ast, envlst);
	set_keypress(in);
	clear_tokenlst(&tokenlst);
	delete_tree(&ast);
}
