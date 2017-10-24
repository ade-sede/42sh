/*
**	program          : linebreak complete_commands linebreak
**	                 | linebreak
*/

int exec_program(t_ast *ast) {
	if (ast->child[1])
		return (exec(ast->child[1]));
}
