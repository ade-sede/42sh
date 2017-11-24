#include "parser.h"
#include <ncurses.h>

void		free_ast_node(void *ast_node)
{
	free_ast(((t_ast_lst *)ast_node)->ast);
}

t_state_lst	*new_state_lst(int n)
{
	t_state_lst *new;

	new = ft_memalloc(sizeof(t_state_lst));
	new->state = n;
	return (new);
}

t_ast_lst	*new_ast_lst(t_ast *ast)
{
	t_ast_lst *new;

	new = ft_memalloc(sizeof(t_ast_lst));
	new->ast = ast;
	return (new);
}
