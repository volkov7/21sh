/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_job_misk.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 16:00:15 by jsance            #+#    #+#             */
/*   Updated: 2020/07/06 16:00:16 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

t_job	*create_job(void)
{
	t_job	*new;

	new = (t_job*)malloc(sizeof(t_job));
	if (new == NULL)
		return (NULL);
	new->andor = 0;
	new->processes = NULL;
	new->last_proc = NULL;
	new->next = NULL;
	return (new);
}

t_job	*get_last_job(t_job **jobs)
{
	t_job	*tmp;

	tmp = *jobs;
	while (tmp->next)
		tmp = tmp->next;
	return (tmp);
}

t_proc	*create_proc(void)
{
	t_proc	*new;

	new = (t_proc*)malloc(sizeof(t_proc));
	if (new == NULL)
		return (NULL);
	new->pid = UNINIT;
	new->env = NULL;
	new->binary = NULL;
	new->argv = NULL;
	new->is_builtin = 0;
	new->exit_status = 0;
	new->redir = NULL;
	new->node = NULL;
	new->next = NULL;
	return (new);
}

int		job_add_proc(t_job *job)
{
	t_proc	*proc;
	t_proc	*tmp;

	proc = create_proc();
	if (proc == NULL)
		return (FUNC_ERROR);
	if (job->processes == NULL)
		job->processes = proc;
	else
	{
		tmp = job->processes;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = proc;
	}
	job->last_proc = proc;
	return (FUNC_SUCCESS);
}

void	clear_jobs(t_job **jobs)
{
	t_proc	*del;
	t_proc	*del_proc;
	t_job	*tmp;

	while (*jobs != NULL)
	{
		tmp = *jobs;
		del = tmp->processes;
		while (del != NULL)
		{
			del_proc = del;
			del = del->next;
			free(del_proc);
		}
		*jobs = (*jobs)->next;
		free(tmp);
	}
}
