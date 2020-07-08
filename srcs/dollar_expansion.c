/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_expansion.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 14:48:33 by jsance            #+#    #+#             */
/*   Updated: 2020/07/06 14:55:25 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		is_env_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

char	*ft_strndup(char *str, size_t n)
{
	char	*fresh;

	fresh = ft_strnew(n);
	if (fresh == NULL)
		return (NULL);
	ft_strncpy(fresh, str, n);
	return (fresh);
}

int		envvar_expansion(char **str, size_t *i, t_envlist *envlst)
{
	size_t	dollar_i;
	char	*env_var;
	char	*env_value;

	dollar_i = *i;
	(*i)++;
	while (is_env_char((*str)[*i]))
		(*i)++;
	if (*i == dollar_i + 1)
		return (FUNC_FAIL);
	if (!(env_var = ft_strndup(&(*str)[dollar_i + 1], *i - dollar_i - 1)))
		return (shell_err(E_ALLOC_MEMORY, NULL, EXIT_FAILURE));
	env_value = get_env_value(env_var, envlst);
	ft_strdel(&env_var);
	if (replace_value(str, env_value, dollar_i, *i - dollar_i) == FUNC_ERROR)
		return (FUNC_ERROR);
	if (env_value != NULL)
		dollar_i += ft_strlen(env_value);
	*i = dollar_i;
	return (FUNC_SUCCESS);
}

int		question_expansion(char **str, size_t *i)
{
	char	*exit_str;
	size_t	dollar_i;

	dollar_i = *i;
	(*i) += 2;
	if ((exit_str = ft_itoa(handle_exit_status(GET_EXIT_STATUS))) == NULL)
		return (shell_err(E_ALLOC_MEMORY, NULL, EXIT_FAILURE));
	if (replace_value(str, exit_str, dollar_i, *i - dollar_i) == FUNC_ERROR)
	{
		ft_strdel(&exit_str);
		return (FUNC_ERROR);
	}
	*i = dollar_i + ft_strlen(exit_str);
	ft_strdel(&exit_str);
	return (FUNC_SUCCESS);
}

int		dollar_expansion(char **str, size_t *i, t_envlist *envlst)
{
	if ((*str)[*i + 1] == '?')
		return (question_expansion(str, i));
	else
		return (envvar_expansion(str, i, envlst));
}
