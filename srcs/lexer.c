#include "lexer.h"
#include <stdio.h>

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

int				tokenlst_addback(t_tokenlst **token_lst, int flags, char *str, t_tokens type)
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
	if (c != '\0' && ft_strchr("-~$/\\'\"", c) != NULL)
		return (1);
	return (0);
}

static	void	lexer_set_flags(t_token *token, char c)
{
	if (is_spec(c))
		token->flags |= HAS_SPECIAL;
	if (c == '"')
		token->flags ^= DQUOTE_STATE;
	if (c == '\'')
		token->flags ^= QUOTE_STATE;
}

void			lexer_state_word_esc(t_token *token)
{
	if (CURRENT_CHAR != '\0')
		lexer_change_state(token, &lexer_state_word);
}

int				is_shellspec(char c)
{
	if (c == '\n' || (ft_strchr("|><;&", c) != NULL))
		return (1);
	return (0);
}

void			lexer_state_word(t_token *token)
{
	if (is_spec(CURRENT_CHAR))
		token->flags |= HAS_SPECIAL;
	if (CURRENT_CHAR == '"' && (token->flags & QUOTE_STATE) == 0)
		token->flags ^= DQUOTE_STATE;
	if (CURRENT_CHAR == '\'' && (token->flags & DQUOTE_STATE) == 0)
		token->flags ^= QUOTE_STATE;
	if (CURRENT_CHAR == '\\' && (token->flags & QUOTE_STATE) == 0)
		lexer_change_state(token, &lexer_state_word_esc);
	else if (is_shellspec(CURRENT_CHAR) == 0 && ft_isblank(CURRENT_CHAR) == 0
			&& CURRENT_CHAR != '\0')
		lexer_change_state(token, &lexer_state_word);
	else if (((token->flags & QUOTE_STATE) || (token->flags & DQUOTE_STATE))
			&& CURRENT_CHAR != '\0')
		lexer_change_state(token, &lexer_state_word);
	else
		token->tk_type = WORD;
}

void			lexer_change_state(t_token *token, void(*lexer_state)(t_token *token))
{
	(token->str_index)++;
	(token->tk_len)++;
	lexer_state(token);
}

void			lexer_state_orif(t_token *token)
{
	token->tk_type = OR_IF;
}

void			lexer_state_pipe(t_token *token)
{
	if (CURRENT_CHAR == '|')
		lexer_change_state(token, &lexer_state_orif);
	else
		token->tk_type = PIPE;
}

void			lexer_state_dgreat(t_token *token)
{
	token->tk_type = DGREAT;
}

void			lexer_state_greatand(t_token *token)
{
	token->tk_type = GREATAND;
}

void			lexer_state_great(t_token *token)
{
	if (CURRENT_CHAR == '>')
		lexer_change_state(token, &lexer_state_dgreat);
	else if (CURRENT_CHAR == '&')
		lexer_change_state(token, &lexer_state_greatand);
	else
		token->tk_type = GREAT;
}

void			lexer_state_dless(t_token *token)
{
	token->tk_type = DLESS;
}

void			lexer_state_lessand(t_token *token)
{
	token->tk_type = LESSAND;
}

void			lexer_state_less(t_token *token)
{
	if (CURRENT_CHAR == '<')
		lexer_change_state(token, &lexer_state_dless);
	else if (CURRENT_CHAR == '&')
		lexer_change_state(token, &lexer_state_lessand);
	else
		token->tk_type = LESS;
}

void			lexer_state_semicol(t_token *token)
{
	token->tk_type = SEMICOL;
}

void			lexer_state_ionum(t_token *token)
{
	if (ft_isdigit(CURRENT_CHAR))
		lexer_change_state(token, &lexer_state_ionum);
	else if (CURRENT_CHAR == '>' || CURRENT_CHAR == '<')
		token->tk_type = IO_NUMBER;
	else
		lexer_state_word(token);
}

void			lexer_state_newline(t_token *token)
{
	token->tk_type = NEWLINE;
}

void			lexer_state_and_if(t_token *token)
{
	token->tk_type = AND_IF;
}

void			lexer_state_bg(t_token *token)
{
	if (CURRENT_CHAR == '&')
		lexer_change_state(token, &lexer_state_and_if);
	else
		token->tk_type = BG;
}

void			lexer_state_start(t_token *token)
{
	lexer_set_flags(token, CURRENT_CHAR);
	if (CURRENT_CHAR == '|')
		lexer_change_state(token, &lexer_state_pipe);
	else if (CURRENT_CHAR == '&')
		lexer_change_state(token, &lexer_state_bg);
	else if (CURRENT_CHAR == '>')
		lexer_change_state(token, &lexer_state_great);
	else if (CURRENT_CHAR == '<')
		lexer_change_state(token, &lexer_state_less);
	else if (CURRENT_CHAR == ';')
		lexer_change_state(token, &lexer_state_semicol);
	else if (CURRENT_CHAR == '\\')
		lexer_change_state(token, &lexer_state_word_esc);
	else if (CURRENT_CHAR == '\n')
		lexer_change_state(token, &lexer_state_newline);
	else if (ft_isdigit(CURRENT_CHAR))
		lexer_change_state(token, &lexer_state_ionum);
	else
		lexer_change_state(token, &lexer_state_word);
}

static int		ft_isblank(char c)
{
	if (c == ' ' || c == '\t')
		return (1);
	return (0);
}

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

void			clear_tokenlst(t_tokenlst **tokenlst)
{
	t_tokenlst	*del;

	while (*tokenlst != NULL)
	{
		del = *tokenlst;
		*tokenlst = (*tokenlst)->next;
		free(del);
	}
}

void			delete_tree(t_ast **ast)
{
	if (*ast == NULL)
		return ;
	delete_tree(&(*ast)->left);
	delete_tree(&(*ast)->right);
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
		ast = NULL;
		tokenlst = NULL;
		lexer(&line, &tokenlst);
		// print_lex(tokenlst);
		printf("\n");
		parser_start(&tokenlst, &ast);
		// print_tree(ast, 0, 0);
		exec_complete_command(ast, envlst);
		clear_tokenlst(&tokenlst);
		delete_tree(&ast);
		free(line);
		line = NULL;
	}
	return (0);
}