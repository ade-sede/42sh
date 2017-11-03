#include "exec.h"

/*
** function_body    : compound_command                
**                  | compound_command redirect_list 
*/

int exec_function_body(t_ast *ast)
{
	return (exec(ast->child[0]));
}
