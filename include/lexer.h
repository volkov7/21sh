#ifndef LEXER_H
# define LEXER_H

# include <stdlib.h>
# include <dirent.h>
# include <sys/stat.h>
# include "../libft/libft.h"

# define FUNC_ERROR			-1
# define FUNC_FAIL			0
# define FUNC_SUCCESS		1
# define UNINIT				-1
# define TOKEN_CHAR			token.str[token.str_index]
# define CURRENT_CHAR		token->str[token->str_index]
# define TOKEN_TYPE			(*token_lst)->type
# define HAS_SPECIAL		(1 << 0)
# define QUOTE_STATE		(1 << 1)
# define DQUOTE_STATE		(1 << 2)
# define GET_EXIT_STATUS	1337

/*
**----------------------------------environment--------------------------------
*/

typedef struct	s_envlist
{
	char				*value;
	struct s_envlist	*next;
}				t_envlist;

/*
**----------------------------------lexer--------------------------------------
*/

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
	BG,
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
	t_tokens			tk_type;
	int					tk_len;
	char				*str;
	int					str_index;
	int					flags;
}				t_token;

/*
**----------------------------------parser-------------------------------------
*/

typedef struct	s_ast
{
	t_tokens			type;
	char				*str;
	int					flags;
	struct s_ast		*left;
	struct s_ast		*right;	
}				t_ast;

/*
**----------------------------------execution----------------------------------
*/

typedef enum			e_andor
{
	ANDOR_NONE,
	ANDOR_AND,
	ANDOR_OR
}						t_andor;

typedef struct	s_proc
{
	pid_t				pid;
	char				**env;
	char				**argv;
	char				*binary;
	int					exit_status;
	t_ast				*redir_and_assign;
	t_ast				*node;
	struct s_proc		*next;
}				t_proc;

typedef	struct	s_job
{
	t_andor				andor;
	t_proc				*processes;
	t_proc				*last_proc;
	struct s_job		*next;
}				t_job;



void			lexer_state_word(t_token *token);
static int		ft_isblank(char c);
void			lexer_change_state(t_token *token, void(*lexer_state)(t_token *token));
int				parser_cmd_sufix(t_tokenlst **token_lst, t_ast **ast,
						t_ast **last_cmd_arg, t_ast **last_prefix);
int				parser_start(t_tokenlst **token_lst, t_ast **ast);
void			print_tree(t_ast *ast, int space, int depth);
char			*get_token_str(t_tokens type);// mb need delete
void			print_lex(t_tokenlst *token_lst);
int				exec_complete_command(t_ast *ast, t_envlist *envlst);
void			launch_job(t_job *job, t_envlist *envlst);

#endif