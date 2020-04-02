#include "lexer.h"

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
	{
		if ((argv = (char**)malloc(sizeof(char*) * 2)) == NULL)
			return (NULL);
		argv[0] = ft_strdup("cat");
		argv[1] = NULL;
		return (argv);
		
	}
	argv[numb_args] = NULL;
	return (argv);	
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

int		prepare_argv_proc(char ***argv, t_ast *node, t_proc *proc,
												t_envlist *envlst)
{
	if (handle_expansions(node, envlst) == FUNC_ERROR)
		return (FUNC_ERROR);
	if (node->type == WORD)
		proc->redir = node->right;
	else
		proc->redir = node;
	*argv = create_proc_argv(node);
	// print_tree(node, 0, 0);
	if (*argv == NULL)
		return (shell_err(E_ALLOC_MEMORY, NULL, EXIT_FAILURE));
	return (FUNC_SUCCESS);
}
