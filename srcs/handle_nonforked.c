#include "lexer.h"

int		handle_non_forked(t_job *job, int fds[3], int pipes[2],
											t_envlist **envlst)
{
	if (job->processes->is_builtin == 1 && job->processes->next == NULL)
	{
		if (ft_strequ(job->processes->argv[0], "exit") == 1)
			execution_builtin(job->processes, envlst);
		else if (ft_strequ(job->processes->argv[0], "cd") == 1)
			execution_builtin(job->processes, envlst);
		else if (ft_strequ(job->processes->argv[0], "setenv") == 1)
			execution_builtin(job->processes, envlst);
		else if (ft_strequ(job->processes->argv[0], "unsetenv") == 1)
			execution_builtin(job->processes, envlst);
		if (ft_strequ(job->processes->argv[0], "exit")
		|| ft_strequ(job->processes->argv[0], "cd")
		|| ft_strequ(job->processes->argv[0], "setenv")
		|| ft_strequ(job->processes->argv[0], "unsetenv"))
		{
			clean_after_fork(job->processes, fds, pipes);
			return (FUNC_SUCCESS);
		}
	}
	return (FUNC_FAIL);
}
