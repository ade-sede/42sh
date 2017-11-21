#include "exec.h"

/*
**	brace_group      : Lbrace compound_list Rbrace
*/

int exec_brace_group(t_ast *ast)
{
	return (exec(ast->child[1]));
}
