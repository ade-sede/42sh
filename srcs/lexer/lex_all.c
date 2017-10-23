#include "t_token.h"
#include "lexer.h"

int				lex_all(t_lexer *lex, t_list **token_list)
{
	t_token		*token;
	t_list		*node;
	int			reopen;

	reopen = 0;
	while ((token = start_lex(lex, &reopen)) != NULL)
	{
		if (!(node = exec_expand(token)))
			node = ft_simple_lst_create(token);
		else
			free_token(token);
		ft_simple_lst_pushback(&lex->stack, node);
	}
	*token_list = lex->stack;
	if (reopen)
		return (reopen);
	return (LEXER_SUCCESS);
}
