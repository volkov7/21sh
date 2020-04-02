#include "lexer.h"

size_t	len_env_list(t_envlist *envlst)
{
	size_t		len;
	t_envlist	*tmp;

	len = 0;
	tmp = envlst;
	while (tmp != NULL)
	{
		len++;
		tmp = tmp->next;
	}
	return (len);
}

char	**env_lst_to_arr(t_envlist *envlst)
{
	char		**env;
	size_t		len;
	size_t		i;
	t_envlist	*tmp;

	len = len_env_list(envlst);
	env = (char**)malloc(sizeof(char*) * len + 1);
	if (env == NULL)
		return (NULL);
	i = 0;
	tmp = envlst;
	while (i < len)
	{
		env[i] = ft_strdup(tmp->value);
		if (env[i] == NULL)
		{
			ft_strarrdel(&env);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	env[len] = NULL;
	return (env);
}

char	*get_env_value(char *var, t_envlist *envlst)
{
	t_envlist	*tmp;
	size_t		len;

	tmp = envlst;
	len = ft_strlen(var);
	while (tmp != NULL)
	{
		if (ft_strnequ(var, tmp->value, len) == 1 && tmp->value[len] == '=')
			return (ft_strchr(tmp->value, '=') + 1);
		tmp = tmp->next;
	}
	return (NULL);
}
