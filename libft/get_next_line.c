/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/20 08:03:35 by nriker            #+#    #+#             */
/*   Updated: 2019/09/22 21:41:25 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static t_list	*get_old(t_list **old, const int fd)
{
	t_list	*copy;

	if (!*old)
		if (!(*old = ft_lstnew("\0", 1)))
			return (NULL);
	copy = *old;
	while (copy->next && copy->content_size != (size_t)fd)
		copy = copy->next;
	if (copy->content_size == (size_t)fd)
		return (copy);
	if (!(copy->next = ft_lstnew("\0", 1)))
		return (NULL);
	copy->next->content_size = fd;
	return (copy->next);
}

static t_list	*read_buf(t_list *copy)
{
	int		red;
	int		i;
	char	buf[BUFF_SIZE + 1];

	while ((red = read(copy->content_size, buf, BUFF_SIZE)))
	{
		i = -1;
		buf[red] = '\0';
		while (red--)
		{
			++i;
			if (buf[i] == '\n' || buf[i] == 0)
			{
				if (!(copy->content = ft_strjoinfree(copy->content, buf)))
					return (NULL);
				return (copy);
			}
		}
		if (!(copy->content = ft_strjoinfree(copy->content, buf)))
			return (NULL);
	}
	return (copy);
}

static char		*get_line(char **line, t_list *copy)
{
	char	*str;

	if (!(ft_strchr(copy->content, '\n')))
	{
		if (!(*line = ft_strdup(copy->content)))
			return (NULL);
		free(copy->content);
		copy->content = "\0";
		return (*line);
	}
	else if (ft_strchr(copy->content, '\n') == NULL)
		*line = "\n";
	else if (!(*line = ft_strcut(copy->content, '\n')))
		return (NULL);
	if (!(str = ft_strdup((ft_strchr(copy->content, '\n') + 1))))
		return (NULL);
	free(copy->content);
	copy->content = str;
	return (*line);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*old;
	t_list			*copy;
	char			s;

	if (BUFF_SIZE < 1 || (read(fd, &s, 0) < 0))
		return (-1);
	if (!(copy = get_old(&old, fd)))
		return (-1);
	if (!(copy = read_buf(copy)))
		return (-1);
	if (ft_strlen(copy->content) == 0)
		return (0);
	if (!(*line = get_line(line, copy)))
		return (-1);
	return (1);
}
