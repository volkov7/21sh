/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_state_great.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsance <jsance@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 15:57:21 by jsance            #+#    #+#             */
/*   Updated: 2020/07/06 15:57:22 by jsance           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"

void			lexer_state_dgreat(t_token *token)
{
	token->tk_type = DGREAT;
}

void			lexer_state_greatand(t_token *token)
{
	token->tk_type = GREATAND;
}

void			lexer_state_great(t_token *token)
{
	if (CURRENT_CHAR == '>')
		lexer_change_state(token, &lexer_state_dgreat);
	else if (CURRENT_CHAR == '&')
		lexer_change_state(token, &lexer_state_greatand);
	else
		token->tk_type = GREAT;
}
