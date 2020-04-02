#include "lexer.h"
#include <stdio.h>//don't forget delete

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
		if (!(str = ft_strnew((size_t)token->tk_len)))
			return (FUNC_ERROR);
		if (!(ft_strncpy(str, &(token->str[tk_start]), token->tk_len)))
			return (FUNC_ERROR);
	}
	if (tokenlst_addback(&tokenlst, token->flags, str, token->tk_type) == FUNC_ERROR)
		return (FUNC_ERROR);
	return (FUNC_SUCCESS);
}

void			clean_token(t_token *token)
{
	(*token).flags = 0;
	(*token).tk_len = 0;
	(*token).tk_type = ERROR;;
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

int				main(int argc, char **argv, char **env)
{
	// -----getline--------
	char		*line = NULL;
	size_t		linecap = 0;
	ssize_t		linelen;
	// -----getline--------
	t_tokenlst	*tokenlst = NULL;
	t_ast		*ast = NULL;
	t_envlist	*envlst = NULL;

	init_env(env, &envlst);
	while ((linelen = getline(&line, &linecap, stdin)) > 0)
	{
		line[linelen - 1] = '\0';
		// line = ft_strdup("unsetenv MONO_PATH");
		ast = NULL;
		tokenlst = NULL;
		lexer(&line, &tokenlst);
		print_lex(tokenlst);
		printf("\n");
		parser_start(&tokenlst, &ast);
		// print_tree(ast, 0, 0);
		exec_complete_command(ast, &envlst);
		clear_tokenlst(&tokenlst);
		delete_tree(&ast);
		free(line);
		line = NULL;
	}
	return (0);
}