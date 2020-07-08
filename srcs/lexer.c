/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 15:12:58 by jsance            #+#    #+#             */
/*   Updated: 2020/07/06 15:43:21 by jsance           ###   ########.fr       */
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

t_envlist		*create_env_node(char *value)
{
	t_envlist	*fresh;

	fresh = (t_envlist*)malloc(sizeof(t_envlist));
	if (fresh == NULL)
		return (NULL);
	fresh->value = ft_strdup(value);
	fresh->next = NULL;
	return (fresh);
}

void			init_env(char **env, t_envlist **envlst)
{
	size_t		i;
	t_envlist	*tmp;

	if (env && env[0] != NULL)
	{
		i = 0;
		if ((*envlst = create_env_node(env[0])) == NULL)
			exit(1);
		tmp = *envlst;
		while (env[++i])
		{
			tmp->next = create_env_node(env[i]);
			if (tmp->next == NULL)
				exit(1);
			tmp = tmp->next;
		}
	}
	else
	{
		if ((*envlst = create_env_node("\0")) == NULL)
			exit(1);
	}
}

void			clear_tokenlst(t_tokenlst **tokenlst)
{
	t_tokenlst	*del;

	while (*tokenlst != NULL)
	{
		del = *tokenlst;
		*tokenlst = (*tokenlst)->next;
		ft_strdel(&del->str);
		free(del);
	}
}

void			delete_tree(t_ast **ast)
{
	if (*ast == NULL)
		return ;
	delete_tree(&(*ast)->left);
	delete_tree(&(*ast)->right);
	ft_strdel(&(*ast)->str);
	free(*ast);
}

int				is_contain_quote(char *str)
{
	size_t		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"' || str[i] == '\\')
			return (FUNC_SUCCESS);
		i++;
	}
	return (FUNC_FAIL);
}

int				is_valid_delim(t_tokenlst *token)
{
	if (token->type != WORD)
		return (shell_err(E_PARSE_NEAR, get_token_str(token->type), EXIT_FAILURE));
	if (is_contain_quote(token->str) == FUNC_SUCCESS)
	{
		quote_removal(&(token->str), 0);
		token->flags |= HEREDOC_NOEXP;
	}
	handle_exit_status(EXIT_SUCCESS);
	return (FUNC_SUCCESS);
}

int				str_check_spec(char *str)
{
	size_t		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (is_spec(str[i]))
			return (FUNC_SUCCESS);
		i++;
	}
	return (FUNC_FAIL);
}

int				set_input_heredoc(t_tokenlst *token, char **res_line)
{
	if (*res_line == NULL)
		token->str = ft_strnew(0);
	else
		token->str = *res_line;
	if (token->str == NULL)
		return (shell_err(E_ALLOC_MEMORY, NULL, EXIT_FAILURE));
	if (str_check_spec(token->str) == FUNC_SUCCESS)
		token->flags |= HAS_SPECIAL;
	token->flags |= IS_HEREDOC;
	return (FUNC_SUCCESS);
}

int				handle_input_heredoc(t_init *in, t_input *input,
									t_tokenlst *token, char *delim)
{
	char		*line;
	char		*res_line;

	res_line = NULL;
	ft_strdel(&(token->str));
	while (1)
	{
		line = read_input_heredoc(in, input, 2);
		ft_putchar('\n');
		if (ft_strequ(line, delim))
			break ;
		res_line = ft_strjoinfree(res_line, line);
		ft_strdel(&line);
		if (res_line == NULL)
			return (shell_err(E_ALLOC_MEMORY, NULL, EXIT_FAILURE));
	}
	if (set_input_heredoc(token, &res_line) == FUNC_ERROR)
		return (FUNC_ERROR);
	ft_strdel(&line);
	return (FUNC_SUCCESS);
}

int				here_doc(t_tokenlst **tokenlst, t_init *in, t_input *input)
{
	t_tokenlst	*tmp;
	char		*delim;

	tmp = *tokenlst;
	while (tmp != NULL)
	{
		if (tmp->type == DLESS)
		{
			tmp = tmp->next;
			if (is_valid_delim(tmp) == FUNC_ERROR)
				return (FUNC_ERROR);
			if ((delim = ft_strjoin(tmp->str, "\n")) == NULL)
				return (shell_err(E_ALLOC_MEMORY, NULL, EXIT_FAILURE));
			if (handle_input_heredoc(in, input, tmp, delim) == FUNC_ERROR)
				return (FUNC_ERROR);
			ft_strdel(&delim);
		}
		tmp = tmp->next;
	}
	return (FUNC_SUCCESS);
}

int				prepare_lexer(char *line, t_envlist **envlst, t_init *in,
															t_input *input)
{
	t_tokenlst	*tokenlst = NULL;
	t_ast		*ast = NULL;

	ast = NULL;
	tokenlst = NULL;
	lexer(&line, &tokenlst);
	here_doc(&tokenlst, in, input);
	// print_lex(tokenlst);
	// printf("\n");
	parser_start(&tokenlst, &ast);
	// print_tree(ast, 0, 0);
	return_terminal(in);
	exec_complete_command(ast, envlst);
	set_keypress(in);
	clear_tokenlst(&tokenlst);
	delete_tree(&ast);
	return (0);
}
