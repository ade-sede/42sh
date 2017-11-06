#include "parser.h"
#include <ncurses.h>

t_ast	*new_ast(t_token *token, int symbol)
{
	t_ast	*new;

	new = ft_memalloc(sizeof(t_ast));
	new->token = token;
	new->symbol = symbol;
	return (new);
}

void	free_ast(t_ast *ast)
{
	int		i = 0;

	if (!ast)
		return ;
	while (ast->child[i] && i < 7)
	{
		free_ast(ast->child[i]);
		i++;
	}
	free(ast);
}

void	free_ast_node(void *ast_node)
{
	free_ast(((t_ast_lst *)ast_node)->ast);
}
void	aux(t_ast *root, int li, int co, void (printer) (void *))
{
	t_ast	*child[3];
	int		i;

	if (!root)
		return ;
	i = 0;
	while (child[i] && i < 3)
		i++;

	move(li, co);
	(void)printer;
	if (root->symbol != -1)
		printw("%d", root->symbol);	/* Print Hello World		  */
	else
		printw("%d", root->token->id);
	refresh();			/* Print it on to the real screen */
	aux(root->child[0], li + 2, co + (0 - i / 3) * 10, printer);
	aux(root->child[1], li + 2, co + (1 - i / 3) * 10, printer);
	aux(root->child[2], li + 2, co + (2 - i / 3) * 10, printer);
}

void	ast_print(t_ast *root, void (printer) (void *))
{

	if (!root)
		return ;
	aux(root, 0,  COLS / 2, printer);
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
