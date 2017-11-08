#include "t_token.h"
#include "lexer.h"
#include <stdio.h>

int				lex_all(t_lexer *lex, t_list **token_list)
{
	t_token		*token;
	t_list		*node;
	int			reopen;

	reopen = 0;
	while ((token = start_lex(lex, &reopen)) != NULL)
	{
//		if (!(node = exec_expand(token)))
			node = ft_simple_lst_create(token);
//		else
//			free_token(token);
		ft_simple_lst_pushback(token_list, node);
	//	printf(MAG"#"CYN"%s, %d"MAG"#\n"RESET , ((t_token *)node->data)->value, ((t_token *)node->data)->id);
	}
	if (reopen)
		return (reopen);
	return (LEXER_SUCCESS);
}
