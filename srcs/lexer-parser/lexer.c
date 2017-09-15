#include "lexer.h"
#include "libft.h"
#include "parser.h"
#include "exec.h"
#include "builtin.h"
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

t_list	*start_lex(t_lexer *lex)
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
**	Rajouter le token qu'on vient de creer a lex->stack
**	exec_expand prend la t_list lex->stack en argument.
**	Se base sur le dernier token.
*/

int		tokenize(t_lexer *lex, size_t token_start, size_t token_end)
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
