#include "exec.h"
/*
** do_group         : Do compound_list Done            'Apply rule 6'
**					;
*/ 
int exec_do_group(t_ast *ast)
{
	return (exec(ast->child[1]));
}
