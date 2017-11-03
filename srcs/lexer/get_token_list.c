

/*
**	PARAMS:
**		lex is the address of an already existing lexer.
**		token_list is the address of a t_list, where all generated tokens must be
**		stored in the right order (reading order).
**		alias_list is the list of valid alias used to expand command words.
**	
**	LOCAL VARIABLES:
**		token is used to received the token from get_token();
**		node is a t_list node that will be appended to token_list. It either
**		the node containing the generated token, or the list of token generated
**		after alias expansion.
**	
**	RETURN_VALUE:
**		Returns the state at the top of the lexer's state stack at the end of the function.
**		Upon successful completion, this state shall be DEFAULT. Otherwise,
**		this state will be used to handle error appropriately (reopen prompt /
**		abort command).
*/

/*
**	This function's job is concatening a list of tokens (returned one by one by
**	the get_token() function), and concatenate them in a list of tokens, after
**	applying alias expansion if necessary.  As for each alias expansion many
**	tokens can be generated, and alias_expansion being recursive, this function
**	will be called again within alias expansion.
*/

/*
**	Comments and whitespaces are delimited too for syntax coloring purposes,
**	but the parser has no uses for them, so they should be discarded here.
*/

int		get_token_list(t_lexer *lex, t_list **token_list, t_list *aliast_list)
{
	t_token	*token;
	t_list	*node;

	while ((token = get_token(lex)) != NULL)
	{
		/* If token is a whitespace or a comment, discard it. Otherwise proceed to concatenation */

		/* If token is a cmd_name, alias expand it. */
		/* if (!(node = expand_alias(lex, token, alias_list))) */
		/* 	node = ft_simple_lst_create(token); */
		/* else */
		node = ft_simple_lst_create(token);
		ft_simple_lst_pushback(token_list, node);
	}
}
