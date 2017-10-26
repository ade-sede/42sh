#include "libft.h"
#include <unistd.h>
#include "env.h"
#include "exec.h"
#include "builtin.h"
#include "color.h"
#include "line_editing.h"
#include "lexer.h"
#include "parser.h"
#include <signal.h>

/*
**	The first time exec_tree is called, we give it our root node as an
**	argument. Depending on the node symbol, it will start the execution of the
**	various commands.
*/

int			exec_tree(t_ast *ast, t_job_control *jc)
{
	t_token		*token;

	token = NULL;
	if (ast)
	{
		if (ast->symbol == SIMPLE_COMMAND)
		{
			check_pipes(ast, head);
			if (head->middle)
				head->middle = head->middle->next;
		}
		else if (ast->symbol == COMPLEXE_COMMAND)
		{
			token = ast->token;
			if (token->id == TK_PIPE)
				return (exec_pipe(ast, head));
			else if (token->id == TK_SEMI)
				return (semi_colon(ast, head));
			else if (token->id == TK_AND_IF)
				return (logical_and(ast, head));
			else if (token->id == TK_OR_IF)
				return (logical_or(ast, head));
		}
	}
	return (ast ? 0 : 1);
}