/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_buf_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: root <root@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 15:01:06 by nriker            #+#    #+#             */
/*   Updated: 2020/05/05 02:00:30 by root             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int		check_binary(char *word)
{
	struct stat	st;

		// if (!access(word, 1))
		if (access(word, F_OK) != -1 || access(word, X_OK) != -1)
		{
			ft_printf("%s ", word);
			return (0);
		}
	if (!lstat(word, &st) && !S_ISDIR(st.st_mode)
			&& !S_ISLNK(st.st_mode))
	{
		
	}
	return (1);
}

void			get_path_dirs(t_input *input)
{
	char	*line;

	if (!(line = getenv("PATH")))
		return ;
	input->path_dirs = ft_strsplit(line, ':');
}

static int	get_buf_size(t_input *i)
{
	int				j;
	int				k;
	DIR				*dir;
	struct dirent	*d;

	k = 0;
	j = 0;
	get_path_dirs(i);
	if (i->path_dirs)
		while (i->path_dirs[j])
		{
			dir = opendir(i->path_dirs[j]);
			while ((d = readdir(dir)) != NULL)
				if ((!ft_strlen(i->word)
					|| ft_strnequ(d->d_name, i->word, ft_strlen(i->word)))
					&& !ft_strequ(d->d_name, ".") && !ft_strequ(d->d_name, ".."))
				{
					// if (!check_binary(d->d_name))
						k++;
				}
			j++;
			if (dir)
				closedir(dir);
		}
	return (k);
}

char		**get_buf_path(t_input *i)
{
	char			**buf;
	int				k;
	int				j;
	DIR				*dir;
	struct dirent	*d;

	k = 0;
	j = 0;
	if (!(i->list_size = get_buf_size(i)))
		return (0);
		// ft_putchar('W');
	if (!(buf = (char**)malloc((sizeof(char*) * i->list_size + 1))))
		ft_error();
	buf[i->list_size] = 0;
	// ft_putchar('F');
	while (i->path_dirs[j])
	{
		dir = opendir(i->path_dirs[j]);
		while ((d = readdir(dir)) != NULL)
			if ((!ft_strlen(i->word)
				|| ft_strnequ(d->d_name, i->word, ft_strlen(i->word)))
				&& !ft_strequ(d->d_name, ".") && !ft_strequ(d->d_name, ".."))
			{
				// if (!check_binary(d->d_name))
				buf[k++] = ft_strdup(d->d_name);
			}
		j++;
		if (dir)
			closedir(dir);
	}
	qs(buf, i->list_size, 0, i->list_size - 1);
	free_buf(i->path_dirs);
	return (buf);
}
