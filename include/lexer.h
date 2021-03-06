/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 14:48:33 by jsance            #+#    #+#             */
/*   Updated: 2020/08/07 12:54:37 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include <pwd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <dirent.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <uuid/uuid.h>
# include "../libft/libft.h"
# include "ft_21sh.h"

# define FUNC_ERROR			-1
# define FUNC_FAIL			0
# define FUNC_SUCCESS		1
# define UNINIT				-1
# define WITE_ANY			-1
# define EXIT_NOT_FOUND		127
# define EXIT_NOT_EXECUTE	126
# define CTRLD				256
# define TOKEN_CHAR			token.str[token.str_index]
# define CURRENT_CHAR		token->str[token->str_index]
# define TOKEN_TYPE			(*token_lst)->type
# define HAS_SPECIAL		(1 << 0)
# define QUOTE_STATE		(1 << 1)
# define DQUOTE_STATE		(1 << 2)
# define HEREDOC_NOEXP		(1 << 3)
# define IS_HEREDOC			(1 << 4)
# define ECHO_OPT_SMALL_N	(1 << 0)
# define ECHO_OPT_SMALL_E	(1 << 1)
# define ECHO_OPT_E			(1 << 2)
# define CD_OPT_P			(1 << 0)
# define CD_OPT_L			(1 << 1)
# define CD_OPT_PRINT		(1 << 2)
# define ENV_OPT_I			(1 << 0)
# define GET_EXIT_STATUS	1337
# define OPEN_FLAGS			O_RDONLY | O_CREAT | O_NONBLOCK
# define GREAT_OPEN_FLAGS	O_WRONLY | O_CREAT | O_TRUNC
# define DGREAT_OPEN_FLAGS	O_WRONLY | O_CREAT | O_APPEND
# define PERMISSIONS		S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
# define E_CD_MANY_ARG		"cd: too many arguments"
# define E_CD_NOT_IN_PWD	"cd: string not in pwd: "
# define E_CD_CANT_GET_CWD	"cd: can't get current working directory"
# define E_CD_NO_EXIST		"cd: no such file or directory: "
# define E_CD_NO_PERM		"cd: permission denied: "
# define E_CD_NOT_A_DIR		"cd: not a directory: "
# define E_TOO_FEW_ARGS		"setenv: Too few arguments\n"
# define E_TOO_MANY_ARGS	"setenv: Too many arguments\n"
# define E_ALLOC_MEMORY		"failed to allocate enough memory\n"
# define E_ILLEGAL_OPT		"illegal option -- "
# define E_IT_BUILTIN		"utility operand is builtin!"
# define E_CANT_GET_CWD		"can't get current working directory\n"
# define E_HOME_NOT_SET		"environment value HOME not set\n"
# define E_NO_SUCH_USRDIR	"21sh: no such user or named directory: "
# define E_IS_DIR			"21sh: is a directory: "
# define E_CREATE_OPEN		"21sh: failed to open or create: "
# define E_CANT_CREAT_PIPE	"21sh: Unable to create pipe\n"
# define E_BAD_FD			"21sh: Bad file descriptor: "
# define E_FILEN_NUMBER		"21sh: file number expected\n"
# define E_NO_EXIST			"21sh: no such file or directory: "
# define E_DUP_FAIL			"21sh: failed to duplicate file descriptor\n"
# define E_FORK_FAIL		"21sh: fork failed\n"
# define E_CANT_GET_STAT	"21sh: could not get stat info of file: "
# define E_NO_PERM			"21sh: permission denied: "
# define E_NOT_FOUND		"21sh: command not found: "
# define E_PARSE_NEAR		"21sh: parse error near "

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
	size_t				tk_len;
	char				*str;
	size_t				str_index;
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
	int					is_builtin;
	int					exit_status;
	t_ast				*redir;
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
void			lexer_change_state(t_token *token,
						void(*lexer_state)(t_token *token));
int				parser_cmd_sufix(t_tokenlst **token_lst, t_ast **ast,
						t_ast **last_cmd_arg, t_ast **last_prefix);
int				parser_start(t_tokenlst **token_lst, t_ast **ast);
char			*get_token_str(t_tokens type);
void			running_proc(void);
int				exec_complete_command(t_ast *ast, t_envlist **envlst);
void			launch_job(t_job *job, t_envlist **envlst);
int				is_redirect(t_tokens type);
int				handle_exit_status(int exit_status);
char			*get_env_value(char *var, t_envlist *envlst);
void			builtin_echo(char **argv);
void			builtin_exit(char **argv);
void			clean_after_fork(t_proc *proc, int fds[3], int pipes[2]);
char			*ft_join_str_str_str(char *s1, char *s2, char *s3);
t_envlist		*create_env_node(char *value);
int				change_dir(char *argpath, int opt, t_envlist **envlst);
void			cd_handle_exit(t_proc *proc, int exit_status);
int				cd_error(char *usedpath, char *argpath, char **newpath,
															char **cwd);
int				shell_err(char *error, char *arg, int exit_status);
void			shell_void_err(char *error, char *arg, int exit_status);
char			*shell_char_err(char *error, char *arg, int exit_status);
void			shell_exit_err(char *error, char *arg, int exit_status);
void			print_err(char *err, char *arg);
int				set_env(t_envlist **envlst, char *var, char *value);
void			create_newpath(char **newpath, char *argpath);
void			chk_two_arguments(char **argv, t_proc *proc,
								t_envlist **envlst, int opt);
void			builtin_cd(char **argv, t_envlist **envlst, t_proc *proc);
void			builtin_setenv(char **argv, t_envlist **envlst, t_proc *proc);
void			builtin_unsetenv(char **arg, t_envlist **envlst, t_proc *proc);
int				find_builtin(char *command);
void			check_binary(char *filename, char **binary, t_envlist *envlst);
void			builtin_env(t_proc *proc, t_envlist *envlst);
char			*canonical_form(char *cwd, char *argpath);
int				find_binary(char *filename, char **binary, t_envlist *envlst);
void			builtin_type(char **argv, t_envlist *envlst);
void			lexer_state_bg(t_token *token);
void			lexer_state_and_if(t_token *token);
void			lexer_state_pipe(t_token *token);
void			lexer_state_great(t_token *token);
void			lexer_state_less(t_token *token);
void			lexer_state_ionum(t_token *token);
void			lexer_state_word(t_token *token);
void			lexer_state_word_esc(t_token *token);
void			lexer_state_start(t_token *token);
int				ft_isblank(char c);
int				is_spec(char c);
int				tokenlst_addback(t_tokenlst **token_lst, int flags, char *str,
																t_tokens type);
int				is_redirect(t_tokens type);
int				return_ast_del(t_ast **ast);
int				add_right_node(t_tokenlst **token_lst, t_ast **ast,
					int (*parser_func)(t_tokenlst **, t_ast **));
int				ast_addnode(t_tokenlst **token_lst, t_ast **ast);
t_ast			*create_new_node(t_tokenlst *token);
int				parser_command(t_tokenlst **token_lst, t_ast **ast);
int				parser_io_redirect(t_tokenlst **token_lst, t_ast **ast);
int				parser_cmd_arg(t_tokenlst **token_lst, t_ast **ast,
						t_ast **last_cmd_arg, t_ast **last_prefix);
void			clear_jobs(t_job **jobs);
int				job_add_proc(t_job *job);
t_job			*get_last_job(t_job **jobs);
t_job			*create_job(void);
int				fork_job(t_job *job, int fds[3], int pipe[2],
													t_envlist **envlst);
int				prepare_argv_proc(char ***argv, t_ast *node, t_proc *proc,
															t_envlist *envlst);
void			ft_strarrdel(char ***arr);
int				dquote_spec(char c);
int				handle_expansions(t_ast *node, t_envlist *envlst);
int				search_spec(t_ast *node, t_envlist *envlst);
int				tilde_expansion(t_ast *node, size_t *i, t_envlist *envlst);
int				replace_value(char **str, char *value, size_t start,
															size_t len);
int				dollar_expansion(char **str, size_t *i, t_envlist *envlst);
int				is_builtin(char *command, t_proc **proc);
void			check_binary(char *filename, char **binary, t_envlist *envlst);
int				handle_non_forked(t_job *job, int fds[3], int pipes[2],
													t_envlist **envlst);
void			launch_child_proc(t_proc *proc, int fds[3], int pipe[2],
													t_envlist **envlst);
int				validate_binary(char *binary);
void			execution_builtin(t_proc *proc, t_envlist **envlst);
int				handle_redirs(t_ast *redir);
void			exec_proc(t_proc *proc, t_envlist **envlst);
char			**env_lst_to_arr(t_envlist *envlst);
void			initial_set_fd(t_ast *redir, char **file, int *stream_fd,
																int flag);
int				set_fd(int *fd, char *word_fd);
int				close_fd(int fd);
void			prepare_lexer(char *line, t_envlist **envlst, t_init *in,
															t_input *input);
void			init_env(char **env, t_envlist **envlst);
void			quote_removal(char **str, int is_heredoc);
void			remove_heredoc_baskslash(char **str, size_t *i, size_t *rep);
void			remove_backslash(char **str, size_t *i, size_t *rep);
void			set_keypress(t_init *in);
t_envlist		*get_envlst(t_envlist *envlst);
void			child_need_to_die(void);
int				here_doc(t_tokenlst **tokenlst, t_init *in, t_input *input);
int				is_contain_quote(char *str);
void			ft_realloc(char **line, const char *buf);
int				set_input_heredoc(t_tokenlst *token, char **res_line);
void			delete_tree(t_ast **ast);
void			clear_tokenlst(t_tokenlst **tokenlst);

#endif
