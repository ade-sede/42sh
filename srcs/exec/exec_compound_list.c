/*
**	compound_list    : linebreak term
**	                 | linebreak term separator
*/

int exec_compound_list(t_ast *ast)
{
	return (exec(ast->child[1]));
}
