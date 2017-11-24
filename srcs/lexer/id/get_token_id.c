/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token_id.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 20:26:25 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/23 20:28:35 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"

/*
**	Returns TRUE if the token can be identified as a reserved word, FALSE
**	othwerwise.  Failure condition: - Token is quoted in some way (dquotes ||
**	quotes)
**
**	Succes condition: True if at least one is true.  - Token can be a command
**	name - Previous token id'ed as a reserved word && Previous token is
**	different from TK_FOR, TK_CASE, TK_IN - Previous token id'ed as TK_NEWLINE
**	- The third TK_WORD / RESERVED_WORD before current token id'ed as TK_FOR or
**	TK_CASE
*/

/*
**	Must reset cmd_name only if the last operator wasnt a redir
*/

static int	check_prev_one_id(t_lexer *lex)
{
	t_token	*token;
	t_list	*node;

	token = NULL;
	node = NULL;
	node = lex->reversed_list;
	if (!node)
		return (TRUE);
	token = node->data;
	if (token->id != TK_LESS && token->id != TK_GREAT \
			&& token->id != TK_DLESS && token->id != TK_DGREAT \
			&& token->id != TK_LESSAND && token->id != TK_GREATAND)
		return (TRUE);
	return (FALSE);
}

void		get_token_id(t_lexer *lex, t_token *token)
{
	struct s_info	*info;

	info = token->state_info;
	if (info->state == OPERATOR)
	{
		token->id = id_operator(token->value);
		if (token->id == TK_AND_IF || token->id == TK_OR_IF || \
			token->id == TK_PIPE \
			|| token->id == TK_SEMI || token->id == TK_CLOBBER)
			lex->cmd_name_open = TRUE;
	}
	else if (info->state == NEWLINE)
		token->id = TK_NEWLINE;
	else if (info->state != COMMENT && info->state != WHITESPACE)
	{
		token->id = id_word(lex, token);
		if (token->id == TK_WORD && check_prev_one_id(lex) \
				&& lex->cmd_name_open)
		{
			token->cmd_name = TRUE;
			lex->cmd_name_open = FALSE;
		}
	}
}
