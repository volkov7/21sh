#include "lexer.h"

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
