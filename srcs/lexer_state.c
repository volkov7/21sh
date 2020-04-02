#include "lexer.h"

static	void	lexer_set_flags(t_token *token, char c)
{
	if (is_spec(c))
		token->flags |= HAS_SPECIAL;
	if (c == '"')
		token->flags ^= DQUOTE_STATE;
	if (c == '\'')
		token->flags ^= QUOTE_STATE;
}

void			lexer_change_state(t_token *token, void(*lexer_state)(t_token *token))
{
	(token->str_index)++;
	(token->tk_len)++;
	lexer_state(token);
}

void			lexer_state_semicol(t_token *token)
{
	token->tk_type = SEMICOL;
}

void			lexer_state_newline(t_token *token)
{
	token->tk_type = NEWLINE;
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
