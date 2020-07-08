/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_job.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 14:48:33 by jsance            #+#    #+#             */
/*   Updated: 2020/07/06 14:56:06 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

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

int		set_status(t_proc **proc, int status)
{
	(*proc)->exit_status = handle_exit_status(WEXITSTATUS(status));
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

	opt = 0;
	pid = waitpid(WAIT_ANY, &status, opt);
	while (found_process(pid, status, jobs) == FUNC_SUCCESS)
		pid = waitpid(WAIT_ANY, &status, opt);
}

void	launch_job(t_job *job, t_envlist **envlst)
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
		ret = fork_job(tmp, fds, pipe, envlst);
		jobs_get_status(&job);
		handle_andor(&tmp);
	}
}
