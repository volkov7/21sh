#include "lexer.h"
#include <stdio.h>//don't forget delete

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
	new->pid = -1;
	new->env = NULL;
	new->binary = NULL;
	new->argv = NULL;
	new->exit_status = 0;
	new->redir_and_assign = NULL;
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

int		exec_command(t_ast *ast, t_job **jobs)
{
	t_job	*job;

	job = get_last_job(jobs);
	if (job_add_proc(job) == FUNC_ERROR)
		exit(1);
	job->last_proc->node = ast;
	return (FUNC_SUCCESS);
}

int		exec_pipe_sequence(t_ast *ast, t_job **jobs)
{
	if (ast->type != PIPE)
		return(exec_command(ast, jobs));
	if (ast->left->type == PIPE)
	{
		if (exec_pipe_sequence(ast->left, jobs) == FUNC_ERROR)
			return (FUNC_ERROR);
	}
	else if (exec_command(ast->left, jobs) == FUNC_ERROR)
		return (FUNC_ERROR);
	return (exec_command(ast->right, jobs) == FUNC_ERROR);
}

int		exec_and_or(t_ast *ast, t_job **jobs)
{
	if (ast->type != AND_IF && ast->type != OR_IF)
	{
		if (*jobs != NULL)
			get_last_job(jobs)->next = create_job();
		else
			*jobs = create_job();
		if (*jobs == NULL)
			return (FUNC_ERROR);
		return(exec_pipe_sequence(ast, jobs));
	}
	if (exec_and_or(ast->left, jobs) == FUNC_ERROR)
		return (FUNC_ERROR);
	if (ast->type == AND_IF || ast->type == OR_IF)
		get_last_job(jobs)->andor = ast->type - 3;
	if (exec_and_or(ast->right, jobs) == FUNC_ERROR)
		return (FUNC_ERROR);
	return (FUNC_SUCCESS);
}

int		exec_list(t_ast *ast, t_job **jobs)
{
	if (ast->type != SEMICOL)
		return (exec_and_or(ast, jobs));
	if (exec_and_or(ast->left, jobs) == FUNC_ERROR)
		return (FUNC_ERROR);
	if (ast->right != NULL)
	{
		if (exec_list(ast->right, jobs) == FUNC_ERROR)
			return (FUNC_ERROR);
	}
	return (FUNC_SUCCESS);
}

int		exec_complete_command(t_ast *ast, t_envlist *envlst)
{
	t_job	*jobs;

	jobs = NULL;
	if (ast == NULL)
		return (FUNC_ERROR);
	if (exec_list(ast, &jobs) == FUNC_ERROR)
		return (FUNC_ERROR);
	// ---------------------------------------------
	// t_job	*tmp;
	// t_proc	*tmp2;
	// tmp = jobs;
	// while (tmp)
	// {
	// 	int		i = 0;
	// 	tmp2 = tmp->processes;
	// 	while(tmp2)
	// 	{
	// 		write(1, "\n", 1);
	// 		print_tree(tmp2->node, 0, 0);
	// 		printf("process = %d\n", i);
	// 		printf("andor = %d\n", tmp->andor);
	// 		i++;
	// 		write(1, "===========", 11);
	// 		tmp2 = tmp2->next;
	// 	}
	// 	tmp = tmp->next;
	// }
	// ---------------------------------------------
	launch_job(jobs, envlst);
	return (FUNC_SUCCESS);
}
