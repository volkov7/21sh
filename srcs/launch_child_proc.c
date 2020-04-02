#include "lexer.h"

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

int		check_if_dir(char *filename)
{
	struct stat st;

	if (stat(filename, &st) == 0)
	{
		if (S_ISDIR(st.st_mode))
			return (shell_err(E_IS_DIR, filename, EXIT_FAILURE));
	}
	return (FUNC_SUCCESS);
}

int		check_valid_file(char *filename)
{
	int		fd;

	fd = open(filename, OPEN_FLAGS, PERMISSIONS);
	if (fd == -1)
		return(shell_err(E_CREATE_OPEN, filename, EXIT_FAILURE));
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

void	launch_child_proc(t_proc *proc, int fds[3], int pipe[2],
											t_envlist *envlst)
{
	if (create_file(proc->redir) == FUNC_ERROR
	|| handle_fds(fds, pipe) == FUNC_ERROR
	|| handle_redirs(proc->redir) == FUNC_ERROR)
		exit(EXIT_FAILURE);
	proc->env = env_lst_to_arr(envlst);
	if (proc->env == NULL)
	{
		ft_putstr_fd(E_ALLOC_MEMORY, 2);
		exit(EXIT_FAILURE);
	}
	exec_proc(proc, &envlst);
}
