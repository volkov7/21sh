/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_buf21sh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 14:29:38 by nriker            #+#    #+#             */
/*   Updated: 2020/08/15 14:20:25 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_21sh.h"

static int		get_buf_size(t_input *i)
{
	int				k;
	DIR				*dir;
	struct dirent	*d;
	char			buffer[151];

	k = 0;
	dir = opendir(getcwd(buffer, 150));
	if (dir != NULL)
	{
		while ((d = readdir(dir)) != NULL)
			if ((!ft_strlen(i->word)
				|| ft_strnequ(d->d_name, i->word, ft_strlen(i->word)))
				&& !ft_strequ(d->d_name, ".") && !ft_strequ(d->d_name, ".."))
				k++;
	}
	if (dir)
		closedir(dir);
	return (k);
}

void			get_buf21sh_cycle(t_input *i, DIR *dir,
					char **buf, struct dirent *d)
{
	int				k;

	k = 0;
	if (dir != NULL)
	{
		while ((d = readdir(dir)) != NULL)
			if ((!ft_strlen(i->word)
				|| ft_strnequ(d->d_name, i->word, ft_strlen(i->word)))
				&& !ft_strequ(d->d_name, ".") && !ft_strequ(d->d_name, ".."))
				buf[k++] = ft_strdup(d->d_name);
	}
	if (dir)
		closedir(dir);
}

char			**get_buf21sh(t_input *i)
{
	char			**buf;
	DIR				*dir;
	char			buffer[151];
	struct dirent	*d;

	d = NULL;
	buf = NULL;
	if (!(i->list_size = get_buf_size(i)))
		return (0);
	if (!(buf = (char**)malloc((sizeof(char*) * (i->list_size + 1)))))
		ft_error();
	buf[i->list_size] = 0;
	dir = opendir(getcwd(buffer, 150));
	get_buf21sh_cycle(i, dir, buf, d);
	qs(buf, i->list_size, 0, i->list_size - 1);
	return (buf);
}
