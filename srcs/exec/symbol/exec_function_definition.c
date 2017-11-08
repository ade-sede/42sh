#include "exec.h"

/*
** function_definition : fname '(' ')' linebreak function_body
*/

t_lst_func	*func_lst_new(t_ast *fct_body, char *fname)
{
	t_lst_func	*new;
	
	new = ft_memalloc(sizeof(t_lst_func));
	new->fct_body = dup_ast(fct_body);
	new->fname = ft_strdup(fname);
	return (new);
}

int exec_function_definition(t_ast *ast)
{
	ft_genlst_add(&singleton_env()->first_func, func_lst_new(ast->child[4], ast->child[0]->child[0]->token->value));
	return (EXIT_SUCCESS);
}
