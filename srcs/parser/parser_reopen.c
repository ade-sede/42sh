#include "parser.h"
#include "color.h"
#include <stdio.h>
#include "exec.h"

int				check_reopen(t_ast_lst *ast_stack, t_list *token)
{
	int		reopen;

	(void)ast_stack;
	if ((reopen = ((t_token*)token->data)->id) == 666 || reopen == 42)
		return (PARSER_REOPEN);
	dprintf(2, "42sh: parse error near `%s'\n", ((t_token*)token->data)->value);
	return (PARSER_ERROR);
}
