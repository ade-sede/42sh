#include "exec.h"

int		is_token(t_ast *ast, int token_id)
{
	if (ast && ast->token && ast->token->id == token_id)
		return (1);
	return (0);
}

int		is_symb(t_ast *ast, int symbol)
{
	if (ast && ast->symbol == symbol)
		return (1);
	return (0);
}
