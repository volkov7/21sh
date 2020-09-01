/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd_create_newpath.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 16:13:55 by jsance            #+#    #+#             */
/*   Updated: 2020/08/16 10:06:10 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void	skip_dot(char *c, size_t *i)
{
	if (c[1] == '/')
		(*i) += 2;
	else
		(*i) += 1;
}

void	one_step_back(char **newpath, char *argpath, size_t *i)
{
	size_t	len;

	len = ft_strlen(*newpath);
	if (len > 0)
		len--;
	while (len > 0 && (*newpath)[len] == '/')
	{
		(*newpath)[len] = '\0';
		len--;
	}
	while (len > 0 && (*newpath)[len] != '/')
	{
		(*newpath)[len] = '\0';
		len--;
	}
	if (argpath[2] == '/')
		(*i) += 3;
	else
		(*i) += 2;
}

void	copy_dir(char **newpath, char *argpath, size_t *i)
{
	size_t	len;

	len = ft_strlen(*newpath);
	if (len != 0 && (*newpath)[len - 1] != '/')
	{
		(*newpath)[len] = '/';
		len++;
	}
	while (argpath[*i] != '/' && argpath[*i] != '\0')
	{
		(*newpath)[len] = argpath[*i];
		len++;
		(*i)++;
	}
	(*newpath)[len] = '\0';
}

void	remove_trailing_slash(char **newpath)
{
	size_t	len;

	len = ft_strlen(*newpath);
	if (len > 0)
		len--;
	while (len > 0 && (*newpath)[len] == '/')
	{
		(*newpath)[len] = '\0';
		len--;
	}
}

void	create_newpath(char **newpath, char *argpath)
{
	size_t	i;

	i = 0;
	while (argpath[i] != '\0')
	{
		while (argpath[i] == '/')
			i++;
		if (argpath[i] != '\0')
		{
			if (ft_strnequ(&argpath[i], "..", 2)
				|| ft_strnequ(&argpath[i], "../", 3))
				one_step_back(newpath, argpath, &i);
			else if (argpath[i] == '.' || ft_strnequ(&argpath[i], "./", 2))
				skip_dot(&argpath[i], &i);
			else
				copy_dir(newpath, argpath, &i);
		}
	}
	remove_trailing_slash(newpath);
}
