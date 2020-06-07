/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 15:00:51 by nriker            #+#    #+#             */
/*   Updated: 2019/12/02 17:52:12 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strcut(const char *s, int c)
{
	char	*str;
	size_t	i;

	i = 0;
	if (!s || !ft_strchr(s, c))
		return (NULL);
	while (s[i] != (char)c)
		i++;
	if ((str = ft_strnew(i + 1)))
		return (ft_strncpy(str, s, i));
	return (NULL);
}
