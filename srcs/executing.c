#include "lexer.h"

void	execution_builtin(t_proc *proc, t_envlist **envlst)
{
	if (ft_strequ(proc->argv[0], "exit"))
		builtin_exit(proc->argv);
	else if (ft_strequ(proc->argv[0], "echo"))
		builtin_echo(proc->argv);
	else if (ft_strequ(proc->argv[0], "cd"))
		builtin_cd(proc->argv, envlst, proc);
	else if (ft_strequ(proc->argv[0], "setenv"))
		builtin_setenv(proc->argv, envlst, proc);
	else if (ft_strequ(proc->argv[0], "unsetenv"))
		builtin_unsetenv(proc->argv, envlst, proc);
	else if (ft_strequ(proc->argv[0], "env"))
		builtin_env(proc, *envlst);
	else if (ft_strequ(proc->argv[0], "type"))
		builtin_type(proc->argv, *envlst);
}

void	exec_proc(t_proc *proc, t_envlist **envlst)
{
	if (proc->is_builtin == 0)
	{
		if (proc->binary != NULL)
			execve(proc->binary, proc->argv, proc->env);
		exit(handle_exit_status(GET_EXIT_STATUS));
	}
	execution_builtin(proc, envlst);
}
