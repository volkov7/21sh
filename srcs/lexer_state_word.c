#include "lexer.h"

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

void			lexer_state_ionum(t_token *token)
{
	if (ft_isdigit(CURRENT_CHAR))
		lexer_change_state(token, &lexer_state_ionum);
	else if (CURRENT_CHAR == '>' || CURRENT_CHAR == '<')
		token->tk_type = IO_NUMBER;
	else
		lexer_state_word(token);
}
