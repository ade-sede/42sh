/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/26 15:56:59 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/06 15:59:36 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "libft.h"
#include "parser.h"
#include <stdio.h>

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

t_ast	*start_lex(t_lexer *lex)
{
	size_t	token_start;
	ssize_t	ret;
	size_t	token_end;
	t_ast	*ast;
#ifdef LEXER_DEBUG
	t_list	*list_start;
#endif

	token_start = 0;
	token_end = 0;
	ast = NULL;
	while (lex->line[lex->index])
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
#ifdef LEXER_DEBUG
	list_start = NULL;
	ft_simple_lst_dup(&list_start, lex->stack);
	ast = ast_create_node(NULL, NULL, SIMPLE_COMMAND);
	ast = ast_separator(&ast, &(list_start));
#else
	ast = ast_create_node(NULL, NULL, SIMPLE_COMMAND);
	ast = ast_separator(&ast, &(lex->stack));
#endif
	return (ast);
}

int		tokenize(t_lexer *lex, size_t token_start, size_t token_end)
{
	char	*value;
	t_token	*token;
	t_list	*node;

	value = ft_strsub(lex->line, token_start, token_end - token_start + 1);
	token = create_token(value, lex->state);
	token->id = lex_get_token_id(token, lex->line[lex->index]);
	node = ft_simple_lst_create(token);
	if (lex->stack == NULL)
		lex->stack = node;
	else
		ft_simple_lst_pushback(&(lex->stack), node);
	return (1);
}
