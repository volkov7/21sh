#include "lexer.h"
#include <stdio.h>

int		shell_err(char *error)
{
	write(2, error, ft_strlen(error));
	return (FUNC_ERROR);
}

size_t	count_args(t_ast *node)
{
	t_ast	*tmp;
	size_t	i;

	i = 0;
	if (node == NULL || node->type != WORD)
		return (0);
	tmp = node;
	while(tmp != NULL && (tmp->type == WORD))
	{
		i++;
		tmp = tmp->left;
	}
	return (i);
}

char	**malloc_argv(size_t numb_args)
{
	char	**argv;

	if (numb_args > 0)
		argv = (char**)malloc(sizeof(char*) * numb_args + 1);
	else
		argv = (char**)malloc(sizeof(char*) * 2);// Need think
	argv[numb_args] = NULL;
	return (argv);	
}

void	ft_strarrdel(char ***arr)
{
	size_t 	i;

	i = 0;
	if (arr != NULL && *arr != NULL)
	{
		while ((*arr)[i] != NULL)
		{
			ft_strdel(&(*arr)[i]);
			i++;
		}
		free(*arr);
		*arr = NULL;
	}
}

char	**create_proc_argv(t_ast *node)
{
	char	**argv;
	size_t	numb_args;
	size_t	i;
	t_ast	*tmp;

	numb_args = count_args(node);
	argv = malloc_argv(numb_args);
	if (argv == NULL)
		return (NULL);
	i = 0;
	tmp = node;
	while (i < numb_args)
	{
		if ((argv[i] = ft_strdup(tmp->str)) == NULL)
		{
			ft_strarrdel(&argv);
			return (NULL);
		}
		tmp = tmp->left;
		i++;
	}
	return (argv);
}

int		replace_value(char **str, char *value, size_t start, size_t len)
{
	char	*fresh;
	size_t	value_len;

	if (value != NULL)
		value_len = ft_strlen(value);
	else
		value_len = 0;
	if ((fresh = ft_strnew(ft_strlen(*str) - len + value_len)) == NULL)
	{
		handle_exit_status(EXIT_FAILURE);
		return (FUNC_ERROR);
	}
	ft_strncpy(fresh, *str, start);
	if (value != NULL)
		ft_strcat(fresh, value);
	ft_strcat(fresh, &(*str)[start + len]);
	ft_strdel(str);
	*str = fresh;
	return (FUNC_SUCCESS);
}

int		is_env_char(char c)
{
		if (ft_isalnum(c) || c == '_')
			return (1);
	return (0);
}

char	*ft_strndup(char *str, size_t n)
{
	char	*fresh;

	fresh = ft_strnew(n);
	if (fresh == NULL)
		return (NULL);
	ft_strncpy(fresh, str, n);
	return (fresh);
}

int		envvar_expansion(char **str, size_t *i, t_envlist *envlst)
{
	size_t	dollar_i;
	char	*env_var;
	char	*env_value;

	dollar_i = *i;
	(*i)++;
	while (is_env_char((*str)[*i]))
		(*i)++;
	if (*i == dollar_i + 1)
		return (FUNC_FAIL);
	if ((env_var = ft_strndup(&(*str)[dollar_i + 1], *i - dollar_i - 1)) == NULL)
	{
		handle_exit_status(EXIT_FAILURE);
		return (shell_err("failed to allocate enough memory\n"));
	}
	env_value = get_env_value(env_var, envlst);
	ft_strdel(&env_var);
	if (replace_value(str, env_value, dollar_i, *i - dollar_i) == FUNC_ERROR)
		return (FUNC_ERROR);
	if (env_value != NULL)
		dollar_i += ft_strlen(env_value);
	*i = dollar_i;
	return (FUNC_SUCCESS);
}

int		question_expansion(char **str, size_t *i)
{
	char	*exit_str;
	size_t	dollar_i;

	dollar_i = *i;
	(*i) += 2;
	if ((exit_str = ft_itoa(handle_exit_status(GET_EXIT_STATUS))) == NULL)
	{
		handle_exit_status(EXIT_FAILURE);
		return (shell_err("failed to allocate enough memory\n"));
	}
	if (replace_value(str, exit_str, dollar_i, *i - dollar_i) == FUNC_ERROR)
	{
		ft_strdel(&exit_str);
		return (FUNC_ERROR);
	}
	*i = dollar_i + ft_strlen(exit_str);
	ft_strdel(&exit_str);
	return (FUNC_SUCCESS);
}

int		dollar_expansion(char **str, size_t *i, t_envlist *envlst)
{
	if ((*str)[*i + 1] == '?')
		return (question_expansion(str, i));
	else
		return (envvar_expansion(str, i , envlst));
}

char	*get_login(t_ast *node, size_t i)
{
	size_t	login_len;

	i++;
	login_len = 0;
	while (node->str[i] != '\0' && node->str[i] != '/')
	{
		i++;
		login_len++;
	}
	if (login_len == 0)
		return (ft_strnew(0));
	return (ft_strsub(node->str, i - login_len, login_len));
}

int		get_user_home_path(char *login, char **home_path, t_envlist *envlst)
{
	struct passwd	*user_info;

	if (login[0] == '\0')
	{
		*home_path = get_env_value("HOME", envlst);
		if (*home_path == NULL)
		{
			handle_exit_status(EXIT_FAILURE);
			return (shell_err("environment value HOME not set\n"));
		}
	}
	else
	{
		user_info = getpwnam(login);
		if (user_info == NULL)
		{
			handle_exit_status(EXIT_FAILURE);
			return (shell_err(": no such user or named directory:"));//need print which user
		}
		*home_path = user_info->pw_dir;
	}
	return (FUNC_SUCCESS);
}

int		tilde_expansion(t_ast *node, size_t *i, t_envlist *envlst)
{
	char	*login;
	char	*home_path;
	int		ret;

	home_path = NULL;
	if (node->type == WORD && *i == 0)
	{
		if ((login = get_login(node, *i)) == NULL)
		{
			handle_exit_status(EXIT_FAILURE);
			return (shell_err("failed to allocate enough memory\n"));// Need normal error function
		}
		if (get_user_home_path(login, &home_path, envlst) == FUNC_ERROR)
		{
			ft_strdel(&login);
			return (FUNC_ERROR);
		}
		ret = replace_value(&node->str, home_path, *i, ft_strlen(login) + 1);
		ft_strdel(&login);
		return (ret);
	}
	else
		(*i)++;
	return (FUNC_SUCCESS);
}

void	update_quote(char *quote, char c, size_t *i)
{
	if (*quote == 0x0)
		*quote = c;
	else if (*quote == c)
		*quote = 0x0;
	(*i)++;
}

int		search_spec(t_ast *node, t_envlist *envlst)
{
	char	quote;
	size_t	i;

	i = 0;
	quote = 0x0;
	while (node->str[i] != '\0')
	{
		if (node->str[i] == '\'' || node->str[i] == '\"')
			update_quote(&quote, node->str[i], &i);
		else if (node->str[i] == '$' && quote != '\'')
		{
			if (dollar_expansion(&node->str, &i, envlst) == FUNC_ERROR)
				return (FUNC_ERROR);
		}
		else if (node->str[i] == '~')
		{
			if (tilde_expansion(node, &i, envlst) == FUNC_ERROR)
				return (FUNC_ERROR);
		}
		else
			i++;
	}
	return (FUNC_SUCCESS);
}

int		handle_expansions(t_ast *node, t_envlist *envlst)
{
	if (node == NULL)
		return (FUNC_FAIL);
	if (handle_expansions(node->right, envlst) == FUNC_ERROR)
		return (FUNC_ERROR);
	if (handle_expansions(node->left, envlst) == FUNC_ERROR)
		return (FUNC_ERROR);
	if (node->type == WORD && node->flags & HAS_SPECIAL)
	{
		if (search_spec(node, envlst) == FUNC_ERROR)
			return (FUNC_ERROR);
	}
	return (FUNC_SUCCESS);
}

int		prepare_argv_proc(char ***argv, t_ast *node, t_proc *proc, t_envlist *envlst)
{
	if (handle_expansions(node, envlst) == FUNC_ERROR)
		return (FUNC_ERROR);
	if (node->type == WORD)
		proc->redir_and_assign = node->right;
	else
		proc->redir_and_assign = node;
	*argv = create_proc_argv(node);
	// print_tree(node, 0, 0);
	if (*argv == NULL)
		return (shell_err("failed to allocate enough memory\n"));
	return (FUNC_SUCCESS);
}

void	setup_stdout(t_proc *proc, int fds[3], int pipes[2])
{
	if (proc->next != NULL)
	{
		if (pipe(pipes) < 0)
		{
			write(2, "Unable to create pipe\n", 22);
			exit(1);
		}
		fds[1] = pipes[1];
	}
	else
		fds[1] = STDOUT_FILENO;
}

int		handle_fds(int fds[3], int pipe[2])
{
	if (fds[0] != STDIN_FILENO)
	{
		if (dup2(fds[0], STDIN_FILENO) == -1)
			return (FUNC_ERROR);
		close(fds[0]);
	}
	else if (pipe[0] != UNINIT)
		close(pipe[0]);
	if (fds[1] != STDOUT_FILENO)
	{
		if (dup2(fds[1], STDOUT_FILENO) == -1)
			return (FUNC_ERROR);
		close(fds[1]);
	}
	if (fds[2] != STDERR_FILENO)
	{
		if (dup2(fds[2], STDERR_FILENO) == -1)
			return (FUNC_ERROR);
		close(fds[2]);
	}
	return (FUNC_SUCCESS);
}

size_t	len_env_list(t_envlist *envlst)
{
	size_t		len;
	t_envlist	*tmp;

	len = 0;
	tmp = envlst;
	while (tmp != NULL)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

char	**env_lst_to_arr(t_envlist *envlst)
{
	char		**env;
	size_t		len;
	size_t		i;
	t_envlist	*tmp;

	len = len_env_list(envlst);
	env = (char**)malloc(sizeof(char*) * len + 1);
	if (env == NULL)
		return (NULL);
	i = 0;
	tmp = envlst;
	while (i < len)
	{
		env[i] = ft_strdup(tmp->value);
		if (env[i] == NULL)
		{
			ft_strarrdel(&env);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	env[len] = NULL;
	return (env);
}

void	exec_proc(t_proc *proc)
{
	if (proc->binary != NULL)
		execve(proc->binary, proc->argv, proc->env);
	exit(EXIT_FAILURE);
}

int		check_if_dir(char *filename)
{
	struct stat st;

	if (stat(filename, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
		{
			handle_exit_status(EXIT_FAILURE);
			return (shell_err("is a directory\n"));//Need print what file is a directory
		}
	}
	return (FUNC_SUCCESS);
}

int		check_valid_file(char *filename)
{
	int		fd;

	fd = open(filename, OPEN_FLAGS, PERMISSIONS);
	if (fd == -1)
	{
		handle_exit_status(EXIT_FAILURE);
		return(shell_err("failed to open/create\n"));//Need print which file can't open 
	}
	close(fd);
	return (FUNC_SUCCESS);
}

int		create_file(t_ast *redir)
{
	char	*filename;

	if (redir == NULL)
		return (FUNC_FAIL);
	if (create_file(redir->left) == FUNC_ERROR)
		return (FUNC_ERROR);
	if (redir->type == GREAT || redir->type == DGREAT)
	{
		if (redir->right->type == IO_NUMBER)
			filename = redir->right->left->str;
		else
			filename = redir->right->str;
		if (check_valid_file(filename) == FUNC_ERROR)
			return (FUNC_ERROR);
		if (check_if_dir(filename) == FUNC_ERROR)
			return (FUNC_ERROR);
	}
	return (FUNC_SUCCESS);
}

void	initial_set_fd(t_ast *redir, char **file, int *stream_fd, int flag)
{
	if (redir->right->type == IO_NUMBER)
	{
		*file = redir->right->left->str;
		*stream_fd = ft_atoi((const char *)redir->right->str);
	}
	else
	{
		*file = redir->right->str;
		*stream_fd = (flag ? STDOUT_FILENO : STDIN_FILENO);
	}
}

int		create_heredoc_fd(char *str)
{
	int		pipes[2];

	handle_exit_status(EXIT_FAILURE);
	if (pipe(pipes) == -1)
		return (shell_err("unable to create pipe\n"));
	if (write(pipes[1], str, ft_strlen(str)) == -1)
	{
		close(pipes[0]);
		close(pipes[1]);
		return (FUNC_ERROR);
	}
	close(pipes[1]);
	handle_exit_status(EXIT_SUCCESS);
	return (pipes[0]);
}

int		redirect_input(t_ast *redir)
{
	char	*file;
	int		stream_fd;
	int		fd;

	initial_set_fd(redir, &file, &stream_fd, 0);
	if (redir->type == LESS)
		fd = open(file, O_RDONLY);
	else if (redir->type == DLESS)
		fd = create_heredoc_fd(file);
	if (fd == -1)
		return (shell_err("no permissions/no such file or directory\n"));// need print which file can't be opened
	if (dup2(fd, stream_fd) == -1)
		return (shell_err("failed to duplicate file descriptor\n"));
	if (redir->type == LESS || redir->type == DLESS)
		close(fd);
	return (FUNC_SUCCESS);
}

int		redirect_output(t_ast *redir)
{
	char	*file;
	int		stream_fd;
	int		fd;

	initial_set_fd(redir, &file, &stream_fd, 1);
	if (redir->type == GREAT)
		fd = open(file, GREAT_OPEN_FLAGS, PERMISSIONS);
	else if (redir->type == DGREAT)
		fd = open(file, DGREAT_OPEN_FLAGS, PERMISSIONS);
	if (fd == -1)
		return (shell_err("no permissions/no such file or directory\n"));
	if (dup2(fd, stream_fd) == -1)
		return (shell_err("failed to duplicate file descriptor\n"));
	if (redir->type == GREAT || redir->type == DGREAT)
		close(fd);
	return (FUNC_SUCCESS);
}

int		redirect(t_ast *node)
{
	if (node == NULL)
		return (FUNC_FAIL);
	if (node->type == GREAT || node->type == DGREAT || node->type == GREATAND)
		return (redirect_output(node));
	if (node->type == LESS || node->type == DLESS || node->type == LESSAND)
		return (redirect_input(node));
	return (FUNC_SUCCESS);
}

int		handle_redirs(t_ast *redir)
{
	if (redir == NULL)
		return (FUNC_FAIL);
	if (is_redirect(redir->type))
	{
		if (redirect(redir) == FUNC_ERROR)
			return (FUNC_ERROR);
	}
	if (handle_redirs(redir->left) == FUNC_ERROR)
		return (FUNC_ERROR);
	return (FUNC_SUCCESS);
}

void	launch_child_proc(t_proc *proc, int fds[3], int pipe[2], t_envlist *envlst)
{
	if (create_file(proc->redir_and_assign) == FUNC_ERROR
	|| handle_fds(fds, pipe) == FUNC_ERROR
	|| handle_redirs(proc->redir_and_assign) == FUNC_ERROR)
		exit(EXIT_FAILURE);
	proc->env = env_lst_to_arr(envlst);
	if (proc->env == NULL)
	{
		write(2, "failed to allocate enough memory\n", 33);
		exit(EXIT_FAILURE);
	}
	exec_proc(proc);
}

int		handle_exit_status(int exit_status)
{
	static int	last_exit_status;

	if (exit_status == GET_EXIT_STATUS)
		return (last_exit_status);
	last_exit_status = exit_status;
	return (last_exit_status);
}

void	setup_fork(t_proc *proc, int fds[3], int pipe[2], t_envlist *envlst)
{
	int		status;

	if (proc->pid < 0)
	{
		write(2, "fork failed\n", 12);
		exit(1);
	}
	else if (proc->pid == 0)
		launch_child_proc(proc, fds, pipe, envlst);
	// else
	// {
	// 	// Parent
	// 	wait(&status);
	// 	proc->exit_status = handle_exit_status(WEXITSTATUS(status));
	// }
}

char	*get_env_value(char *var, t_envlist *envlst)
{
	t_envlist	*tmp;
	size_t		len;

	tmp = envlst;
	len = ft_strlen(var);
	while (tmp != NULL)
	{
		if (ft_strnequ(var, tmp->value, len) == 1 && tmp->value[len] == '=')
			return (ft_strchr(tmp->value, '=') + 1);
		tmp = tmp->next;
	}
	return (NULL);
}

int		get_paths(char ***paths, t_envlist *envlst)
{
	char	*path_value;

	path_value = get_env_value("PATH", envlst);
	if (path_value == NULL || *path_value == '\0')
		return (FUNC_FAIL);
	*paths = ft_strsplit(path_value, ':');
	if (paths == NULL)
		return (shell_err("failed to allocate enough memory\n"));
	return (FUNC_SUCCESS);
}

char	*ft_join_str_str_str(char *s1, char *s2, char *s3)
{
	char	*fresh;

	fresh = ft_strnew(ft_strlen(s1) + ft_strlen(s2) + ft_strlen(s3));
	if (fresh == NULL)
		return (NULL);
	ft_strcpy(fresh, s1);
	ft_strcat(fresh, s2);
	ft_strcat(fresh, s3);
	return (fresh);
}

int		check_dir(char *path, char *filename, char **binary, DIR *dir)
{
	struct dirent	*dp;
	struct stat		st;

	while((dp = readdir(dir)) != NULL)
	{
		if (ft_strcmp(dp->d_name, filename) == 0)
		{
			if ((*binary = ft_join_str_str_str(path, "/", filename)) == NULL)
				return (shell_err("failed to allocate enough memory\n"));
			if (lstat(*binary, &st) == -1)
				return (shell_err("could not get stat info of file\n"));
			if (S_ISREG(st.st_mode))
				return (FUNC_SUCCESS);
			ft_strdel(&(*binary));
			return (FUNC_SUCCESS);
		}
	}
	return (FUNC_FAIL);
}

int		check_paths(char **paths, char *filename, char **binary)
{
	DIR		*dir;
	size_t	i;

	i = 0;
	while (paths[i] != NULL)
	{
		dir = opendir(paths[i]);
		if (dir != NULL)
		{
			if (check_dir(paths[i], filename, binary, dir) == FUNC_ERROR)
			{
				closedir(dir);
				ft_strarrdel(&paths);
				return (FUNC_ERROR);
			}
			closedir(dir);
			if (*binary != NULL)
				return (FUNC_SUCCESS);
		}
		i++;
	}
	return (FUNC_FAIL);
}

int		find_binary(char *filename, char **binary, t_envlist *envlst)
{
	char	**paths;

	paths = NULL;
	if (get_paths(&paths, envlst) == FUNC_ERROR)
		return (FUNC_ERROR);
	if (check_paths(paths, filename, binary) == FUNC_ERROR)
		return (FUNC_ERROR);
	ft_strarrdel(&paths);
	if (*binary == NULL)
		return (FUNC_FAIL);
	return (FUNC_SUCCESS);
}

void	handle_andor(t_job **job)
{
	if ((*job)->andor == ANDOR_OR)
	{
		if (handle_exit_status(GET_EXIT_STATUS) != 0)
			*job = (*job)->next;
		else
		{
			while ((*job)->andor == ANDOR_OR)
				*job = (*job)->next;
			*job = (*job)->next;
		}
	}
	else if ((*job)->andor == ANDOR_AND)
	{
		if (handle_exit_status(GET_EXIT_STATUS) == 0)
			*job = (*job)->next;
		else
		{
			while ((*job)->andor == ANDOR_AND)
				*job = (*job)->next;
			*job = (*job)->next;
		}
	}
	else
		*job = (*job)->next;
}

void	clean_after_fork(t_proc *proc, int fds[3], int pipes[2])
{
	if (fds[0] != STDIN_FILENO && fds[0] != UNINIT)
		close(fds[0]);
	if (fds[1] != STDOUT_FILENO && fds[1] != UNINIT)
		close(fds[1]);
	fds[0] = pipes[0];
	if (proc->binary != NULL)
		ft_strdel(&proc->binary);
	if (proc->argv != NULL)
		ft_strarrdel(&proc->argv);
	if (proc->env != NULL)
		ft_strarrdel(&proc->env);
}

int		set_status(t_proc **proc, int status)
{
	// printf("before exit status = %d\n", handle_exit_status(GET_EXIT_STATUS));
	(*proc)->exit_status = handle_exit_status(WEXITSTATUS(status));
	// printf("after exit status = %d\n", handle_exit_status(GET_EXIT_STATUS));
	// if (WIFEXITED((*proc)->exit_status))
	kill((*proc)->pid, SIGINT);
	return (FUNC_SUCCESS);
}

int		found_process(pid_t pid, int status, t_job **jobs)
{
	t_job	*tmp;
	t_proc	*proc;

	if (pid > 0)
	{
		tmp = *jobs;
		while (tmp != NULL)
		{
			proc = tmp->processes;
			while (proc != NULL)
			{
				if (proc->pid == pid)
					return (set_status(&proc, status));
				proc = proc->next;
			}
			tmp = tmp->next;
		}
	}
	return (FUNC_FAIL);
}

void	jobs_get_status(t_job **jobs)
{
	pid_t	pid;
	int		status;
	int		opt;

	// opt = WUNTRACED | WNOHANG;
	opt = 0;
	pid = waitpid(WAIT_ANY, &status, opt);
	while (found_process(pid, status, jobs) == FUNC_SUCCESS)
		pid = waitpid(WAIT_ANY, &status, opt);
}

int		go_fork_job(t_job *job, int fds[3], int pipe[2], t_envlist *envlst)
{
	pid_t	pid;
	t_proc	*proc;
	t_ast	*node;

	proc = job->processes;
	while (proc != NULL)
	{
		node = proc->node;
		if (prepare_argv_proc(&(proc->argv), node, proc, envlst) == FUNC_ERROR)
			return (FUNC_ERROR);
		if (find_binary(proc->argv[0], &proc->binary, envlst) == FUNC_FAIL)
			write(2, "command not found\n", 18);
		setup_stdout(proc, fds, pipe);
		pid = fork();
		proc->pid = pid;
		setup_fork(proc, fds, pipe, envlst);
		clean_after_fork(proc, fds, pipe);
		proc = proc->next;
	}
	return (FUNC_SUCCESS);
}

void	launch_job(t_job *job, t_envlist *envlst)
{
	int		fds[3];
	int		pipe[2];
	int		ret;
	t_job	*tmp;

	tmp = job;
	while (tmp != NULL)
	{
		fds[0] = STDIN_FILENO;
		fds[2] = STDERR_FILENO;
		pipe[0] = UNINIT;
		pipe[1] = UNINIT;
		ret = go_fork_job(tmp, fds, pipe, envlst);
		jobs_get_status(&job);
		handle_andor(&tmp);
	}
}