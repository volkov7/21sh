/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nriker <nriker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/08 17:41:47 by nriker            #+#    #+#             */
/*   Updated: 2020/08/08 17:41:54 by nriker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

static char	*single_tk_str(t_tokens type)
{
	if (type == AND_IF)
		return ("&&");
	else if (type == OR_IF)
		return ("||");
	else if (type == DLESS)
		return ("<<");
	else if (type == DGREAT)
		return (">>");
	else if (type == LESS)
		return ("<");
	else if (type == GREAT)
		return (">");
	else if (type == LESSAND)
		return ("<&");
	else if (type == GREATAND)
		return (">&");
	else if (type == PIPE)
		return ("|");
	else if (type == SEMICOL)
		return (";");
	return ("ERROR");
}

char		*get_token_str(t_tokens type)
{
	if (type == START)
		return ("START");
	else if (type == WORD)
		return ("WORD");
	else if (type == IO_NUMBER)
		return ("IO_NUM");
	else if (type == NEWLINE)
		return ("\\n");
	else if (type == END)
		return ("END");
	else
		return (single_tk_str(type));
}
