#include "exec.h"
/*
**	while_clause     : While compound_list do_group
*/

int exec_while_clause(t_ast *ast)
{
	int		exit_status;
	fprintf(stderr, "coucou\n");
	while ((exit_status = exec(ast->child[1])) == EXIT_SUCCESS)
	{	
		fprintf(stderr, "exit status: %d\n", exit_status);
		exec(ast->child[2]);
	}
	fprintf(stderr, "exit status: %d\n", exit_status);
	return (EXIT_SUCCESS);
}
