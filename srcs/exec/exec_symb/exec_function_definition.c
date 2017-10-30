#include "exec.h"

/*
** function_definition : fname '(' ')' linebreak function_body
**                  ;
** function_body    : compound_command                
**                  | compound_command redirect_list 
*/

int exec_function_definition(t_ast *ast) {
	(void)ast;
	return (1);
}
