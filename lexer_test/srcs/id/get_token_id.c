#include "lexer.h"
#include "libft.h"

/*
**	Returns TRUE if the token can be identified as a reserved word, FALSE othwerwise.
**	Failure condition:
**	- Token is quoted in some way (dquotes || quotes)
**
**	Succes condition: True if at least one is true.
**	- Token can be a command name
**	- Previous token id'ed as a reserved word && Previous token is different from TK_FOR, TK_CASE, TK_IN
**	- Previous token id'ed as TK_NEWLINE
**	- The third TK_WORD / RESERVED_WORD before current token id'ed as TK_FOR or TK_CASE
*/

#include <stdio.h>
static int	check_prev_3(t_lexer *lex)
{
	dprintf(2, "lol\n");
	t_token	*token = NULL;
	t_list	*node = NULL;
	size_t	count;

	count = 0;
	node = lex->reversed_list;
	while (node && 1)
	{
		token = node->data;
		if (token->id != TK_NEWLINE)
			break ;
		node = node->next;
	}
	while (node && count != 1)
	{
		token = node->data;
		if (token->id == TK_WORD || IS_RESERVED_WORD(token->id))
			++count;
		else
			return (FALSE);
		node = node->next;
	}
	if (!node)
		return (FALSE);
	token = node->data;
	if (token->id == TK_FOR || token->id == TK_CASE)
		return (TRUE);
	return (FALSE);
}

/*
**	Problem with case a b \n\n\n in c
*/

static int	check_prev_1(t_lexer *lex)
{
	t_token	*token = NULL;
	t_list	*node = NULL;

	node = ft_simple_lst_get_n(lex->reversed_list, 1);
	if (!node)
		return (FALSE);
	token = node->data;
	if (token->id == TK_NEWLINE)
		return (TRUE);
	/* if (token->id == TK_IF || token->id == TK_THEN || token->id == TK_ELSE || token->id == TK_ELIF || token->id == TK_FI || token->id == TK_DO || token->id == TK_DONE || token->id == TK_ESAC || token->id == TK_WHILE || token->id == TK_UNTIL || token->id == TK_LBRACE || token->id == TK_RBRACE || token->id == TK_BANG || token->id == TK_LPAREN || token->id == TK_RPAREN) */
	if (IS_RESERVED_WORD(token->id) && token->id != TK_FOR && token->id != TK_CASE && token->id != TK_IN)
		return (TRUE);
	return (FALSE);
}

static int	get_reserved_word_status(ssize_t *info, t_lexer *lex)
{
	if (info[_T_STATE] == DQUOTES || info[_T_STATE] == QUOTES)
		return (FALSE);
	if (lex->cmd_name_open)
		return (TRUE);
	if (check_prev_1(lex))
		return (TRUE);
	if (check_prev_3(lex))
		return (TRUE);
	return (FALSE);
}

void	get_token_id(t_lexer *lex, t_token *token)
{
	ssize_t	*info;

	info = token->state_info;

	if (info[_T_STATE] == OPERATOR) // Token is an operator
	{
		token->id = id_operator(token->value);
		if (token->id == TK_AND_IF || token->id == TK_OR_IF || token->id == TK_PIPE || token->id == TK_SEMI || token->id == TK_CLOBBER)
			lex->cmd_name_open = TRUE;
	}
	else if (info[_T_STATE] == NEWLINE) // Token is an operator
		token->id = TK_NEWLINE;
	else if (info[_T_STATE] != COMMENT && info[_T_STATE] != WHITESPACE) // Token is anything else
	{
		if (get_reserved_word_status(info, lex)) // Activation de la detection des mots reserves.
			token->id = id_reserved_words(token->value);
		else
			token->id = TK_WORD;
		if (lex->cmd_name_open)
			lex->cmd_name_open = FALSE;
	}
}
