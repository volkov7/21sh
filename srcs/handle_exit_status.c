/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit_status.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 15:58:32 by jsance            #+#    #+#             */
/*   Updated: 2020/07/06 15:58:33 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

int		handle_exit_status(int exit_status)
{
	static int	last_exit_status;

	if (exit_status == GET_EXIT_STATUS)
		return (last_exit_status);
	last_exit_status = exit_status;
	return (last_exit_status);
}
