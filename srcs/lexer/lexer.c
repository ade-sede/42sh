#include "t_token.h"
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

//void	alias(t_lexer *lex, t_token *token, t_list *forbiden_alias)
//{
	//t_list	*list;

	//lex_all(lex);
	//list = lex->stack;
	//while (lex->stack)
	//{
		//check_alias(lex, list);
		//list = list->next;
	//}
	//ft_simple_lst_pushback(&forbiden_alias, ft_simple_lst_create());
	//return (alias(lex, forbiden_alias));
//}

#include <stdio.h>

t_token			*handle_lexer(t_lexer *lex)
{
	t_token	*token;
	t_list	*node;
	int		reopen;

	if (lex->stack)
		return (lex->stack->data);
	if ((token = start_lex(lex, &reopen)) == NULL)
		return (NULL);
//	if (check_alias(lex, NULL))
//		return (alias(lex, token, NULL));
	if ((node = exec_expand(token)))
		lex->stack = node;
	else
		lex->stack = ft_simple_lst_create(token);
	(void)node;
	token = lex->stack->data;
	return (token);
}


int			lex_all(t_lexer *lex, t_list **token_list)
{
	t_token	*token;
	t_list	*node;
	int		reopen;

	reopen = 0;
	while ((token = start_lex(lex, &reopen)) != NULL)
	{
#ifdef LEXER_DEBUG
		dprintf(2, ""MAG"#"CYN"%s"MAG"#\n"RESET, token->value);
#endif
		if ((node = exec_expand(token)))
			lex->stack = node;
		else
			node = ft_simple_lst_create(token);
		ft_simple_lst_pushback(&lex->stack, node);
	}
	*token_list = lex->stack;
	if (reopen)
		return (reopen);
	return (LEXER_SUCCESS);
}
/*
**	in all case start_lex will create one token or return NULL
*/

t_token			*start_lex(t_lexer *lex, int *reopen)
{
	ssize_t	ret;
	size_t	token_end;

	token_end = 0;
	if (lex->line[lex->index] == '\0')
		return (NULL);
	if (lex->state != DQUOTED && lex->state != QUOTED)
		lex->state = start_token(lex, &lex->token_start);
	if (lex->state == INPUT_END)
		return (NULL);
	while ((ret = token_match(lex, lex->token_start)) == -1)
		lex->index++;
	if (lex->line[lex->index] == '\0' && (lex->state == DQUOTED || lex->state == QUOTED))
	{
#ifdef LEXER_DEBUG
		printf("\nreopen line editing\n");
#endif
		*reopen = lex->state;
		return (NULL);
	}
	token_end = (size_t)ret;
	return (tokenize(lex, lex->token_start, token_end));
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
//	dprintf(2, "%d\n", lex->line[lex->index]);
	*token_start = lex->index;
	ret = update_state(lex);
	lex->index++;
	return (ret);
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
	if (charcmp(lex->line, lex->index, '\n'))
			return (NEWLINE);
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
**	Rajouter le token qu'on vient de creer a lex->stack
**	exec_expand creer un t_list a partir de la valeur etendu de du token.
*/

t_token			*tokenize(t_lexer *lex, size_t token_start, size_t token_end)
{
	char	*value;
	t_token	*token;

	value = ft_strsub(lex->line, token_start, token_end - token_start + 1);
	token = create_token(value, lex->state, lex->line[lex->index]);
	token->id = lex_get_token_id(lex, token);
	lex->last_id = token->id;
	if (TK_IS_SEP(token->id))
		lex->cmd_name_open = 1;
	return (token);
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
	else if (token->type == NEWLINE)
			id = TK_NEWLINE;
	else if (token->type == WORD)
	{
		if (!done)
			done = lex_id_io_number(token, token->delimiter, &id);
		if (!done)
			done = lex_id_word(lex, token, &id);
	}
	else if (token->type == DQUOTED || token->type == QUOTED)
		id = TK_WORD;
	return (id);
}
