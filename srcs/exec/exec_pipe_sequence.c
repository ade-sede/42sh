/*
**	pipe_sequence    :                             command
**	                 | pipe_sequence '|' linebreak command
*/

int exec_pipe_sequence(t_ast *ast)
{
	return (exec(ast->child[0]));
}
