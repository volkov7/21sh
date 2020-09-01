/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_routine.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 16:00:33 by jsance            #+#    #+#             */
/*   Updated: 2020/08/15 13:55:35 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

size_t		len_env_list(t_envlist *envlst)
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

char		**env_lst_to_arr(t_envlist *envlst)
{
	char		**env;
	size_t		len;
	size_t		i;
	t_envlist	*tmp;

	len = len_env_list(envlst);
	env = (char**)malloc(sizeof(char*) * (len + 1));
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

char		*get_env_value(char *var, t_envlist *envlst)
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

t_envlist	*create_env_node(char *value)
{
	t_envlist	*fresh;

	fresh = (t_envlist*)malloc(sizeof(t_envlist));
	if (fresh == NULL)
		return (NULL);
	fresh->value = ft_strdup(value);
	fresh->next = NULL;
	return (fresh);
}

void		init_env(char **env, t_envlist **envlst)
{
	size_t		i;
	t_envlist	*tmp;

	if (env && env[0] != NULL)
	{
		i = 0;
		if ((*envlst = create_env_node(env[0])) == NULL)
			return ;
		tmp = *envlst;
		while (env[++i])
		{
			tmp->next = create_env_node(env[i]);
			if (tmp->next == NULL)
				return ;
			tmp = tmp->next;
		}
	}
	else
	{
		if ((*envlst = create_env_node("\0")) == NULL)
			return ;
	}
}
