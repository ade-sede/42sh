/*
**	compound_command : brace_group
**	                 | subshell
**	                 | for_clause
**	                 | case_clause
**	                 | if_clause
**	                 | while_clause
**	                 | until_clause
*/

int exec_compound_command(t_ast *ast) {
	return (exec(ast->child[0]));
}

