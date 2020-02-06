#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include "./libft/libft.h"

# define FUNC_ERROR		-1
# define FUNC_SUCCESS	1
# define TOKEN_CHAR		token.str[token.str_index]
# define CURRENT_CHAR	token->str[token->str_index]
# define HAS_SPECIAL	(1 << 0)
# define QUOTE_STATE	(1 << 1)
# define DQUOTE_STATE	(1 << 2)

typedef enum	e_tokens
{
	ERROR,
	START,
	WORD,
	IO_NUMBER,
	AND_IF,
	OR_IF,
	DLESS,
	DGREAT,
	LESS,
	GREAT,
	LESSAND,
	GREATAND,
	PIPE,
	SEMICOL,
	NEWLINE,
	END
}				t_tokens;

typedef struct	s_tokenlst
{
	t_tokens			type;
	char				*str;
	int					flags;
	struct s_tokenlst	*next;
}				t_tokenlst;

typedef struct	s_toke
{
	t_tokens	tk_type;
	int			tk_len;
	char		*str;
	int			str_index;
	int			flags;
}				t_token;

void			lexer_state_word(t_token *token);
static int		ft_isblank(char c);
void			lexer_change_state(t_token *token, void(*lexer_state)(t_token *token));

#endif