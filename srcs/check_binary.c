/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_binary.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/02 10:21:30 by jsance            #+#    #+#             */
/*   Updated: 2020/08/02 10:21:58 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		get_paths(char ***paths, t_envlist *envlst)
{
	char	*path_value;

	path_value = get_env_value("PATH", envlst);
	if (path_value == NULL || *path_value == '\0')
		return (FUNC_ERROR);
	*paths = ft_strsplit(path_value, ':');
	if (paths == NULL)
		return (shell_err(E_ALLOC_MEMORY, NULL, EXIT_FAILURE));
	return (FUNC_SUCCESS);
}

int		check_dir(char *path, char *filename, char **binary, DIR *dir)
{
	struct dirent	*dp;
	struct stat		st;

	while ((dp = readdir(dir)) != NULL)
	{
		if (ft_strcmp(dp->d_name, filename) == 0)
		{
			if ((*binary = ft_join_str_str_str(path, "/", filename)) == NULL)
				return (shell_err(E_ALLOC_MEMORY, NULL, EXIT_FAILURE));
			if (lstat(*binary, &st) == -1)
				return (shell_err(E_CANT_GET_STAT, *binary, EXIT_FAILURE));
			if (S_ISREG(st.st_mode))
				return (FUNC_SUCCESS);
			ft_strdel(&(*binary));
			return (FUNC_SUCCESS);
		}
	}
	return (FUNC_FAIL);
}

int		check_paths(char **paths, char *filename, char **binary)
{
	DIR		*dir;
	size_t	i;

	i = 0;
	while (paths[i] != NULL)
	{
		dir = opendir(paths[i]);
		if (dir != NULL)
		{
			if (check_dir(paths[i], filename, binary, dir) == FUNC_ERROR)
			{
				closedir(dir);
				ft_strarrdel(&paths);
				return (FUNC_ERROR);
			}
			closedir(dir);
			if (*binary != NULL)
				return (FUNC_SUCCESS);
		}
		i++;
	}
	return (FUNC_FAIL);
}

int		find_binary(char *filename, char **binary, t_envlist *envlst)
{
	char	**paths;

	paths = NULL;
	if (get_paths(&paths, envlst) == FUNC_ERROR)
		return (FUNC_ERROR);
	if (check_paths(paths, filename, binary) == FUNC_ERROR)
		return (FUNC_ERROR);
	ft_strarrdel(&paths);
	if (*binary == NULL)
		return (FUNC_FAIL);
	return (FUNC_SUCCESS);
}

void	check_binary(char *filename, char **binary, t_envlist *envlst)
{
	if (ft_strchr(filename, '/') == NULL)
	{
		if (find_binary(filename, binary, envlst) == FUNC_SUCCESS)
		{
			if (validate_binary(*binary) == FUNC_ERROR)
				ft_strdel(binary);
		}
		else
			shell_void_err(E_NOT_FOUND, filename, EXIT_NOT_FOUND);
	}
	else
	{
		if (validate_binary(filename) == FUNC_SUCCESS)
			*binary = ft_strdup(filename);
	}
}
