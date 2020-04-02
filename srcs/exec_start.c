#include "lexer.h"
#include <stdio.h>//don't forget delete

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

int		exec_complete_command(t_ast *ast, t_envlist **envlst)
{
	t_job	*jobs;

	jobs = NULL;
	if (ast == NULL)
		return (FUNC_ERROR);
	if (exec_list(ast, &jobs) == FUNC_ERROR)
		return (FUNC_ERROR);
	// ---------------------------------------------
	t_job	*tmp;
	t_proc	*tmp2;
	tmp = jobs;
	while (tmp)
	{
		int		i = 0;
		tmp2 = tmp->processes;
		while(tmp2)
		{
			write(1, "\n", 1);
			print_tree(tmp2->node, 0, 0);
			printf("process = %d\n", i);
			printf("andor = %d\n", tmp->andor);
			i++;
			write(1, "===========", 11);
			tmp2 = tmp2->next;
		}
		tmp = tmp->next;
	}
	write(1, "\n", 1);
	// ---------------------------------------------
	launch_job(jobs, envlst);
	clear_jobs(&jobs);
	return (FUNC_SUCCESS);
}
