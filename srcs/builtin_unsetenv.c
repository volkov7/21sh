#include "lexer.h"

void	delete_env_var(t_envlist **envlst, char *value)
{
	t_envlist	*tmp;
	t_envlist	*prev;
	size_t		len;

	tmp = *envlst;
	len = ft_strlen(value);
	if (tmp != NULL && ft_strnequ(tmp->value, value, len)
							&& tmp->value[len] == '=')
	{
		*envlst = (*envlst)->next;
		ft_strdel(&(tmp->value));
		free(tmp);
	}
	while (tmp != NULL && (ft_strnequ(tmp->value, value, len) == 0
							|| tmp->value[len] != '='))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	prev->next = tmp->next;
	ft_strdel(&(tmp->value));
	free(tmp);
}

void	unsetenv_exit(t_proc *proc, int exit_status)
{
	if (proc->pid == UNINIT)
		handle_exit_status(exit_status);
	else if (proc->pid == 0)
		exit(exit_status);
}

void	unsetenv_error(char *err, t_proc *proc, int exit_status)
{
	write(2, err, ft_strlen(err));
	unsetenv_exit(proc, exit_status);
}

void	builtin_unsetenv(char **arg, t_envlist **envlst, t_proc *proc)
{
	size_t	i;

	i = 1;
	if (arg[i] == 0)
		unsetenv_error(E_TOO_FEW_ARGS, proc, EXIT_FAILURE);
	while (arg[i] != NULL)
	{
		delete_env_var(envlst, arg[i]);
		i++;
	}
	unsetenv_exit(proc, EXIT_SUCCESS);
}
