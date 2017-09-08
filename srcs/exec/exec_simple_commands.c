
#include "libft.h"
#include <unistd.h>
#include "env.h"
#include "exec.h"
#include "builtin.h"
#include "line_editing.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>

/*
**	Atm, this function just frees all node so that it doesnt leaks.
*/

static void	free_redir(t_ast *ast)
{
	t_list	*child_list;
	t_ast	*child_node;

	child_list = ast->child;
	while (child_list)
	{
		child_node = child_list->data;
		free_ast_node(child_node);
		child_list = child_list->next;
	}
}

/*
**	The function exec_simple_command will execute a command, step by step.
**	- Step one is I/O Redirection handling.
**	- Step two is creating an array which contains the command name, and the
**	argument to this command.
**	- Step three is sending this array to the exec function.
**
**	The ast node represents has a simple_command symbol. Treats every child one
**	by one until no childs are left.
*/

static void	treat_node(t_ast *child_node, t_list **redir_stack, \
		char **argv, size_t i)
{
	if (child_node->symbol == IO_REDIRECT)
	{
		exec_redir(child_node->child, redir_stack);
		free_redir(child_node);
	}
	if (child_node->symbol == CMD_NAME || child_node->symbol == CMD_SUFFIX)
		argv[i] = ft_strdup(child_node->token->value);
	free_ast_node(child_node);
}

void		exec_simple_command(t_ast *ast, t_lst_head *head)
{
	t_list		*child_list;
	size_t		i;
	const char	**argv;
	t_list		*redir_stack;

	i = 0;
	redir_stack = NULL;
	child_list = ast->child;
	argv = ft_memalloc(sizeof(*argv) * (ft_lst_len(child_list) + 1));
	while (child_list)
	{
		treat_node(child_list->data, &redir_stack, (char**)argv, i);
		child_list = child_list->next;
		i++;
	}
	exec(singleton_env(), argv, head);
	close_redir(redir_stack);
}
