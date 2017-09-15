
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
		char **argv, size_t *i)
{
	if (child_node->symbol == IO_REDIRECT)
		exec_redir(child_node->child, redir_stack);
	if (child_node->symbol == CMD_NAME || child_node->symbol == CMD_SUFFIX)
		if (child_node->token->id != TK_NEWLINE)
		{
			argv[*i] = ft_strdup(child_node->token->value);
			(*i)++;
		}
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
		treat_node(child_list->data, &redir_stack, (char**)argv, &i);
		child_list = child_list->next;
	}
	exec_dup(redir_stack);
	exec(singleton_env(), argv, head);
	close_dup(redir_stack);
}
