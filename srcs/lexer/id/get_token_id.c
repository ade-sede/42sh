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

/*
**	Problem with case a b \n\n\n in c
*/

/*
**	Must reset cmd_name only if the last operator wasnt a redir
*/

static int	check_prev_one_redir(t_lexer *lex)
{
	t_token	*token = NULL;
	t_list	*node = NULL;

	node = lex->reversed_list;
	if (!node)
		return (TRUE);
	token = node->data;
	if (token->id != TK_LESS && token->id != TK_HERE && token->id != TK_GREAT && token->id != TK_DLESS && token->id != TK_DGREAT && token->id != TK_LESSAND && token->id != TK_GREATAND)
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
		token->id = id_word(lex, token);
		if (token->id != TK_ASSIGNMENT_WORD && lex->cmd_name_open && check_prev_one_redir(lex))
			lex->cmd_name_open = FALSE;
	}
}
