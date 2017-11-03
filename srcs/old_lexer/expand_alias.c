#include "lexer.h"
#include "env.h"
#include "builtin.h"

/*
**	Takes a token (original token). If an alias is found for this token,
**	returns a list of token where each token belongs to the xpanded string. If
**	a match is found, the input token must be free'd from the list, and the
**	generated list returned. If no allowed match is found, NULL is returned.
*/

/*
**	To generate the list of token, another instance of a lexer is called upon
**	the extended string.  This lexer's start state is herited from the lexer
**	used to delimite the original token, and its end state will become the end
**	state of the lexer that called it.  This design is used because alias
**	expansion can be used within alias expansion, and special characters such
**	as separators or quotes can be encountered.
*/

#include <stdio.h>

t_list	*expand_alias(t_lexer *lex, t_token *token, t_list *alias_list)
{
	t_list	*alias_node;
	t_list	*alias_copy;
	t_list	*token_list;
	char	*alias_value;
	t_lexer new_lex;
	ssize_t	eq_index;
	int		ret;

	alias_copy = NULL;
	token_list = NULL;
	if (!alias_list)
		return (NULL);
	ft_simple_lst_dup(&alias_copy, alias_list);
	if ((alias_node = find_alias(alias_copy, token->value, ft_strlen(token->value))) != NULL)
	{
		alias_value = alias_node->data;
		dprintf(2, "%p\n", alias_value);//			REMOVE		
		ft_simple_lst_del_one(&alias_copy, alias_node, NULL);
		eq_index = ft_strichr(alias_value, '=');
		new_lex = init_lexer(alias_value + eq_index + 1);
		new_lex.state = lex->state;
		new_lex.last_id = lex->last_id;
		ret = lex_all(&new_lex, &token_list, alias_copy);
		lex->state = new_lex.state;
	}
	ft_simple_lst_remove(&alias_copy, NULL);
	if (token_list)
		free_token(token);
	return (token_list);
}
