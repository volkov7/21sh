#include "lexer.h"

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

int		prepare_argv_proc(char ***argv, t_ast *node, t_proc *proc)
{
	if (node->type == WORD)
		proc->redir_and_assign = node->right;
	else
		proc->redir_and_assign = node;
	*argv = create_proc_argv(node);
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

void	launch_child_proc(t_proc *proc, int fds[3], int pipe[2], t_envlist *envlst)
{
	// if (handle_fds(fds, pipe) == FUNC_ERROR)
	// 	exit(1);
	proc->env = env_lst_to_arr(envlst);
	if (proc->env == NULL)
	{
		write(2, "failed to allocate enough memory\n", 33);
		exit(1);
	}
	exec_proc(proc);
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
	else
	{
		// Parent
		wait(&status);
		proc->exit_status = WEXITSTATUS(status);
		printf("exit status = %d\n", proc->exit_status);
	}
}

char	*get_env_var(char *var, t_envlist *envlst)
{
	t_envlist	*tmp;
	size_t		len;

	tmp = envlst;
	len = ft_strlen(var);
	while (tmp != NULL)
	{
		if (ft_strnequ(var, tmp->value, len) == 1)
			return (ft_strchr(tmp->value, '=') + 1);
		tmp = tmp->next;
	}
	return (NULL);
}

int		get_paths(char ***paths, t_envlist *envlst)
{
	char	*path_value;

	path_value = get_env_var("PATH=", envlst);
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

int		go_fork_job(t_job *job, int fds[3], int pipe[2], t_envlist *envlst)
{
	pid_t	pid;
	t_proc	*proc;
	t_ast	*node;
	t_job	*tmp;

	tmp = job;
	while (tmp != NULL)
	{
		proc = tmp->processes;
		while (proc != NULL)
		{
			node = proc->node;
			if (prepare_argv_proc(&(proc->argv), node, proc) == FUNC_ERROR)
				return (FUNC_ERROR);
			if (find_binary(proc->argv[0], &proc->binary, envlst) == FUNC_FAIL)
				write(2, "command not found\n", 18);
			pid = fork();
			proc->pid = pid;
			setup_fork(proc, fds, pipe, envlst);
			proc = proc->next;
		}
		tmp = tmp->next;
	}
	return (FUNC_SUCCESS);
}

void	launch_job(t_job *job, t_envlist *envlst)
{
	int		fds[3];
	int		pipe[2];
	int		ret;

	fds[0] = STDIN_FILENO;
	fds[2] = STDERR_FILENO;
	ret = go_fork_job(job, fds, pipe, envlst);
}