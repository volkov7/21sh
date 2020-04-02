#include "lexer.h"

void	setup_stdout(t_proc *proc, int fds[3], int pipes[2])
{
	if (proc->next != NULL)
	{
		if (pipe(pipes) < 0)
		{
			ft_putstr_fd(E_CANT_CREAT_PIPE, 2);
			exit(EXIT_FAILURE);
		}
		fds[1] = pipes[1];
	}
	else
		fds[1] = STDOUT_FILENO;
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

void	setup_fork(t_proc *proc, int fds[3], int pipe[2], t_envlist **envlst)
{
	int		status;

	if (proc->pid < 0)
	{
		ft_putstr_fd(E_FORK_FAIL, 2);
		exit(EXIT_FAILURE);
	}
	else if (proc->pid == 0)
		launch_child_proc(proc, fds, pipe, envlst);
}

int		fork_job(t_job *job, int fds[3], int pipe[2], t_envlist **envlst)
{
	pid_t	pid;
	t_proc	*proc;
	t_ast	*node;

	proc = job->processes;
	while (proc != NULL)
	{
		node = proc->node;
		if (prepare_argv_proc(&(proc->argv), node, proc, *envlst) == FUNC_ERROR)
			return (FUNC_ERROR);
		if (is_builtin(proc->argv[0], &proc) == FUNC_FAIL)
			check_binary(proc->argv[0], &proc->binary, *envlst);
		if (handle_non_forked(job, fds, pipe, envlst) == FUNC_SUCCESS)
			return (FUNC_SUCCESS);
		setup_stdout(proc, fds, pipe);
		pid = fork();
		proc->pid = pid;
		setup_fork(proc, fds, pipe, envlst);
		clean_after_fork(proc, fds, pipe);
		proc = proc->next;
	}
	return (FUNC_SUCCESS);
}
