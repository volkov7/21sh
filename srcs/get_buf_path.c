/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_buf_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 15:01:06 by nriker            #+#    #+#             */
/*   Updated: 2020/08/15 14:06:30 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

void		get_path_dirs(t_input *input)
{
	char	*line;

	if (!(line = getenv("PATH")))
		return ;
	input->path_dirs = ft_strsplit(line, ':');
}

void		get_buf_size_cycle(t_input *i, struct dirent *d, DIR *dir, int *k)
{
	while ((d = readdir(dir)) != NULL)
	{
		if ((!ft_strlen(i->word)
			|| ft_strnequ(d->d_name, i->word, ft_strlen(i->word)))
			&& !ft_strequ(d->d_name, ".") && !ft_strequ(d->d_name, ".."))
		{
			(*k)++;
		}
	}
}

int			get_buf_size(t_input *i)
{
	int				j;
	int				k;
	DIR				*dir;
	struct dirent	*d;

	k = 0;
	j = 0;
	d = NULL;
	get_path_dirs(i);
	if (i->path_dirs)
		while (i->path_dirs[j])
		{
			if ((dir = opendir(i->path_dirs[j])) == NULL)
			{
				j++;
				continue ;
			}
			get_buf_size_cycle(i, d, dir, &k);
			j++;
			if (dir)
				closedir(dir);
		}
	return (k);
}

void		get_buf_path_cycle(t_input *i, struct dirent *d,
	DIR *dir, char **buf)
{
	int		k;
	int		j;

	k = 0;
	j = 0;
	while (i->path_dirs[j])
	{
		if ((dir = opendir(i->path_dirs[j])) == NULL)
		{
			j++;
			continue ;
		}
		while ((d = readdir(dir)) != NULL)
		{
			if ((!ft_strlen(i->word)
				|| ft_strnequ(d->d_name, i->word, ft_strlen(i->word)))
				&& !ft_strequ(d->d_name, ".") && !ft_strequ(d->d_name, ".."))
				buf[k++] = ft_strdup(d->d_name);
		}
		j++;
		if (dir)
			closedir(dir);
	}
}

char		**get_buf_path(t_input *i)
{
	char			**buf;
	DIR				*dir;
	struct dirent	*d;

	if (!(i->list_size = get_buf_size(i)))
	{
		if (i->path_dirs)
			free_buf(i->path_dirs);
		i->path_dirs = NULL;
		return (0);
	}
	if (!i->list_size)
		return (NULL);
	if (!(buf = (char**)malloc((sizeof(char*) * (i->list_size + 1)))))
		ft_error();
	buf[i->list_size] = 0;
	d = NULL;
	dir = NULL;
	get_buf_path_cycle(i, d, dir, buf);
	qs(buf, i->list_size, 0, i->list_size - 1);
	if (i->path_dirs)
		free_buf(i->path_dirs);
	i->path_dirs = NULL;
	return (buf);
}
