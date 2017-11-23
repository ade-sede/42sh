#include "exec.h"

/*
** function_definition : fname '(' ')' linebreak function_body
*/

void		func_lst_free(void *fct)
{
	t_lst_func	*fct_cast;

	fct_cast = fct;
	free_ast_and_token(fct_cast->fct_body);
	ft_strdel(&fct_cast->fname);
}

t_lst_func	*func_lst_new(t_ast *fct_body, char *fname)
{
	t_lst_func	*new;

	new = ft_memalloc(sizeof(t_lst_func));
	new->fct_body = dup_ast(fct_body);
	new->fname = ft_strdup(fname);
	return (new);
}

int			exec_function_definition(t_ast *ast)
{
	char		*fname;
	t_lst_func	*old;

	fname = ast->child[0]->child[0]->token->value;
	if ((old = get_function(singleton_env(), fname)))
		ft_genlst_del_one(&singleton_env()->first_func, old, func_lst_free);
	ft_genlst_add(&singleton_env()->first_func,
			func_lst_new(ast->child[4], fname));
	return (EXIT_SUCCESS);
}
