#include "lexer.h"
#include "libft.h"

static int		check_valid_name(const char *value, size_t size)
{
	size_t	i;

	i = 0;
	while (value[i] && size)
	{
		if (i == 0 && ft_isdigit(value[i]))
			return (FALSE);
		if (!ft_isalnum(value[i]) && value[i] != '_')
			return (FALSE);
		--size;
		++i;
	}
	return (TRUE);
}

static t_token	*check_function_name(t_lexer *lex, const char *value)
{
	int	smooth;
	size_t	count;
	t_list	*node;
	t_token	*token;

	count = 0;
	smooth = TRUE;
	node = lex->reversed_list;
	if (!ft_strequ(value, ")") || !node)
		return (NULL);
	token = node->data;
	if (token->id != TK_LPAREN)
		return (NULL);
	node = node->next;
	if (!node)
		return (NULL);
	token = node->data;
	if (!check_valid_name(token->value, ft_strlen(token->value)))
		token = NULL;
	return (token);
}

static int	check_assignement_word(t_lexer *lex, const char *value)
{
	int		i;
	int		in_exp;
	ssize_t	eq_index;

	i = 0;
	in_exp = -1;
	eq_index = -1;
	if (!lex->cmd_name_open)
		return (FALSE);
	while (value[i])
	{
		if (charcmp(value, i, '$'))
			in_exp = 1;
		if (charcmp(value, i, '='))
			eq_index = i;
		++i;
	}
	if (eq_index == -1 || eq_index == 0 || in_exp < eq_index)
		return (FALSE);
	if (!check_valid_name(value, eq_index + 1))
		return (FALSE);
	return (TRUE);
}

static int	check_io_number(t_token *token)
{

	size_t	i;
	i = 0;
	if (token->delim != '<' && token->delim != '>')
		return (FALSE);
	while (token->value[i])
	{
		if (!ft_isdigit(token->value[i]))
			return (FALSE);
		++i;
	}
	return (TRUE);
}

/* if (token->id == TK_IF || token->id == TK_THEN || token->id ==
** TK_ELSE || token->id == TK_ELIF || token->id == TK_FI || token->id ==
** TK_DO || token->id == TK_DONE || token->id == TK_ESAC || token->id ==
** TK_WHILE || token->id == TK_UNTIL || token->id == TK_LBRACE ||
** token->id == TK_RBRACE || token->id == TK_BANG || token->id ==
** TK_LPAREN || token->id == TK_RPAREN)
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
	if (IS_RESERVED_WORD(token->id) && token->id != TK_FOR && token->id != TK_CASE && token->id != TK_IN)
		return (TRUE);
	return (FALSE);
}

static int	check_prev_3(t_lexer *lex)
{
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


static int	check_for(t_lexer *lex, const char *value)
{
	t_token	*token;

	if (!lex->reversed_list)
		return (FALSE);
	token = lex->reversed_list->data;
	if (token->id != TK_FOR)
		return (FALSE);
	if (!check_valid_name(value, ft_strlen(value)))
		return (FALSE);
	return (TRUE);
}

/*
**	Need to apply a special rule so that word() lets ( and ) be recogniszed
**	as reserved words even if cmd_name is closed.
*/

int		id_word(t_lexer *lex, t_token *token)
{
	t_token	*func_name_token;
	int		id;
	/* Apply prev_1 rule */
	/* Apply name in function rules */
	/* Apply Assignement preceding command name rule */
	/* Apply prev_3 */
	/* Apply name in for */
	/* Apply case statement termination */
	/* Command name rule \\ subshell rule */

	/* This one is non-exclusive */
	if ((func_name_token = check_function_name(lex, token->value)))
		func_name_token->id = TK_NAME;
	if (check_io_number(token))
		id = ft_atoi(token->value);
	else if (check_prev_1(lex))
		id = id_reserved_words(token->value);
	else if (check_assignement_word(lex, token->value))
		id = TK_ASSIGNMENT_WORD;
	else if (check_prev_3(lex))
		id = id_reserved_words(token->value);
	else if (check_for(lex, token->value))
		id = TK_NAME;
	else if (lex->cmd_name_open || ft_strequ("(", token->value) || ft_strequ(")", token->value))
		id = id_reserved_words(token->value);
	else
		id = TK_WORD;
	return (id);
}
