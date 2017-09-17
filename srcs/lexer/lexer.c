/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:41:02 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/17 17:11:46 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "token.h"
#include "lexer.h"

/*
**	We are reading our input line 1 char a time, looking for the delimiter of
**	our token. Everytime we're done matching a token, we reset our token_start
**	wich gives us the index of the first char of the token.
**
**	If the character we are currently reading completes the match :
**	-	Create a token from what we just read.
**	-	Assign an id (type ?) to the token.
**	-	Push this token onto the stack (here adding it at the start of the
**	list).
*/

/*
**		DETERMINING WHERE A TOKEN START AND ENDS :
**
**	See POSIX STANDARDS @ Token Recognition (2.3)
**
**	The last char of the token we matched is either the one we are on, or the
**	one before depending on wether or not we were in a "contained" token.
**	Examples:			`ls .'
**						   ^
**			When we reach this space, we have a match and line[index] == ' ';
**				The token "ls" ends at the char line[index - 1];
**
**			`"This is  a quoted string"ls'
**								      ^
**			When we reach the `"' we have a match. The token ends on this char.
**
**	The index of the last char included in the token should be returned by the
**	token_match() function.
**	We always want index to be on the char following the last char of the token
**	we just closed.
*/

/*
** Token id is determined by the immedaite context of the token and the state
** of the lexer.
*/

t_list			*start_lex(t_lexer *lex)
{
	size_t	token_start;
	ssize_t	ret;
	size_t	token_end;

	token_start = 0;
	token_end = 0;
	while (lex->line && lex->line[lex->index])
	{
		lex->state = start_token(lex, &token_start);
		if (lex->state == INPUT_END)
			break ;
		while ((ret = token_match(lex, token_start)) == -1)
			lex->index++;
		token_end = (size_t)ret;
		tokenize(lex, token_start, token_end);
		lex->state = WORD;
	}
	ft_strdel((char **)&lex->line);
	return (lex->stack);
}

/*
**	Returns the state according to char lex->line[lex->index]
**	Everything that is not Quoted (simple or double) Blackslashed, or a
**	candidate to expansion is considered to be at the default state 'word'.
*/

int				update_state(t_lexer *lex)
{
	if (charcmp(lex->line, lex->index, '\\'))
		return (lex->line[lex->index]);
	if (IS_QUOTED(lex->line[lex->index]))
		return (lex->line[lex->index]);
	else if (IS_OPERATOR(lex->line[lex->index]))
		return (OPERATOR);
	else if (IS_EXPAND(lex->line[lex->index]))
		return (EXPAND);
	if (!lex->line[lex->index])
		return (INPUT_END);
	return (WORD);
}

/*
**	Initialize the token_start index and returns the state according to the
**	first char of the token.
*/

int				start_token(t_lexer *lex, size_t *token_start)
{
	int		ret;

	ret = 0;
	while (lex->line[lex->index] && (IS_WHITESPACE(lex->line[lex->index]) \
				&& lex->line[lex->index] != '\n'))
		lex->index++;
	*token_start = lex->index;
	ret = update_state(lex);
	lex->index++;
	return (ret);
}

/*
**	Rajouter le token qu'on vient de creer a lex->stack
**	exec_expand prend la t_list lex->stack en argument.
**	Se base sur le dernier token.
*/

int				tokenize(t_lexer *lex, size_t token_start, size_t token_end)
{
	char	*value;
	t_token	*token;
	t_list	*node;

	value = ft_strsub(lex->line, token_start, token_end - token_start + 1);
	token = create_token(value, lex->state, lex->line[lex->index]);
	token->id = lex_get_token_id(lex, token);
	lex->last_id = token->id;
	if (TK_IS_SEP(token->id))
		lex->cmd_name_open = 1;
	if (check_alias(lex, token))
		return (1);
	node = exec_expand(token);
	if (lex->stack == NULL)
		lex->stack = node;
	else
		ft_simple_lst_pushback(&(lex->stack), node);
	return (1);
}

/*
**	Trying to determine the ID of the token using its context (delimiter, lexer
**	state). This id will be used by the parser to help assign grammar symbol to
**	the token and build the tree.
*/

t_token_id		lex_get_token_id(t_lexer *lex, t_token *token)
{
	t_token_id	id;
	int			done;

	done = FALSE;
	id = -1;
	if (token->type == OPERATOR)
		id = lex_id_operator(token->value);
	else if (token->type == WORD)
	{
		if (ft_strequ(token->value, "\n"))
		{
			done = TRUE;
			id = TK_NEWLINE;
		}
		if (!done)
			done = lex_id_io_number(token, token->delimiter, &id);
		if (!done)
			done = lex_id_word(lex, token, &id);
	}
	else if (token->type == DQUOTED || token->type == QUOTED)
		id = TK_WORD;
	return (id);
}
