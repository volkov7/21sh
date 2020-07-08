/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 15:58:45 by jsance            #+#    #+#             */
/*   Updated: 2020/07/06 15:58:46 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		shell_err(char *error, char *arg, int exit_status)
{
	ft_putstr_fd(error, 2);
	if (arg != NULL)
		ft_putendl_fd(arg, 2);
	handle_exit_status(exit_status);
	return (FUNC_ERROR);
}

void	shell_void_err(char *error, char *arg, int exit_status)
{
	ft_putstr_fd(error, 2);
	if (arg != NULL)
		ft_putendl_fd(arg, 2);
	handle_exit_status(exit_status);
}
