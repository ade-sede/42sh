#include "t_token.h"
#include "lexer.h"

#include <stdio.h>
int				lex_all(t_lexer *lex, t_list **token_list, t_list *alias_list)
{
	t_token		*token;
	t_list		*node;
	int			reopen;

	reopen = 0;
	while ((token = start_lex(lex, &reopen)) != NULL)
	{
		if (token->cmd_name)
		{
			if (!(node = expand_alias(lex, token, alias_list)))
				node = ft_simple_lst_create(token);
		}
		else
			node = ft_simple_lst_create(token);
#ifdef LEXER_DEBUG
		dprintf(2, "Delimited token "MAG"#"CYN"%s"MAG"# "RESET, token->value);
		dprintf(2, "With ID "MAG"#"RED"%d"MAG"# "RESET, token->id);
		dprintf(2, "With TYPE "MAG"#"YEL"%d"MAG"#\n"RESET, token->type);
#endif
		exec_expand(node);
		ft_simple_lst_pushback(&lex->stack, node);
	}
	*token_list = lex->stack;
	if (reopen)
		return (reopen);
	return (LEXER_SUCCESS);
}

/* if (!(node = exec_expand(token))) */
/* 	node = ft_simple_lst_create(token); */
/* else */
/* 	free_token(token); */
