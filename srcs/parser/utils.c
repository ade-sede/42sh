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
