#include "libft.h"
#include <unistd.h>
#include "env.h"
#include "exec.h"
#include "builtin.h"
#include "color.h"
#include "line_editing.h"
#include "lexer.h"
#include "parser.h"
#include <stdio.h>
#include <errno.h>
#include <signal.h>

/*
** 	List of pipes should be generated during parsing and creation of the tree.
*/

static int	exec_pipe(t_ast *ast, t_lst_head *head)
{
	if (exec_tree(ast->child->data, head) == 0)
		exec_tree(ast->child->next->data, head);
	return (0);
}

int			p_right(t_pipe *pr, t_ast *ast, t_lst_head *head)
{
	pid_t		child;

	child = fork();
	if (child == -1)
	{
		dprintf(2, "fork error = %s\n", strerror(errno));
		return (0);
	}
	if (child == 0)
	{
		if (close(pr->p[READ_END]) == -1)
			dprintf(2, "p_right close read-end error = %s\n",strerror(errno));
		if (dup2(pr->p[WRITE_END], STDOUT_FILENO) == -1)
			dprintf(2, "pright dup2 error = %s\n", strerror(errno));
		exec_simple_command(ast, head);
		exit(0);
	}
	else
	{
		pr->pid = child;
		return (1);
	}
	return (1);
}

int			p_both(t_pipe *pr, t_pipe *pl, t_ast *ast, t_lst_head *head)
{
	pid_t		child;

	child = fork();
	if (child == -1)
	{
		dprintf(2, "fork error = %s\n", strerror(errno));
		return (0);
	}
	if (child == 0)
	{
		if (dup2(pl->p[READ_END], STDIN_FILENO) == -1)
			dprintf(2, "dup2 error  error = %s\n", strerror(errno));
		if (close(pl->p[WRITE_END]) == -1)
			dprintf(2, "p_both close write-end  error = %s\n", strerror(errno));
		if (close(pr->p[READ_END]) == -1)
			dprintf(2, "p_both close read-end  error = %s\n", strerror(errno));
		if (dup2(pr->p[WRITE_END], STDOUT_FILENO) == -1)
			dprintf(2, "p_bothdup2 error  error = %s\n", strerror(errno));
		exec_simple_command(ast, head);
		exit(0);
	}
	else
	{
		if (close(pl->p[WRITE_END]) == -1)
			dprintf(2, "p_both close write-end  error = %s\n", strerror(errno));
		if (close(pl->p[READ_END]) == -1)
			dprintf(2, "p_both close read-end  error = %s\n", strerror(errno));
		pr->pid = child;
	}
	return (1);
}

int		wait_zombies(t_lst_head *head)
{
	t_list_d	*cur;
	t_pipe		*pipe;
	int			ret;

	cur = head->first;
	while (cur)
	{
		pipe = (t_pipe *)cur->data;
		if (pipe)
		{
			if (pipe->pid != 0)
				waitpid(pipe->pid, &ret, 0);
		}
		cur = cur->next;
	}
	return (1);
}

int			p_left(t_pipe *pl, t_ast *ast, t_lst_head *head)
{
	int		save;

	if ((save = dup(STDIN_FILENO)) == -1)
		dprintf(2, "dup error  error = %s\n", strerror(errno));
	if (dup2(pl->p[READ_END], STDIN_FILENO) == -1)
		dprintf(2, "dup2 error  error = %s\n", strerror(errno));
	if (close(pl->p[WRITE_END]) == -1)
		dprintf(2, "p_left close write-end  error = %s\n", strerror(errno));

	exec_simple_command(ast, head);

	if (close(pl->p[READ_END]) == -1)
		dprintf(2, "p_left close read-end  error = %s\n", strerror(errno));
	if (dup2(save, STDIN_FILENO) == -1)
		dprintf(2, "dup2 error  error = %s\n", strerror(errno));
	if (close(save) == -1)
		dprintf(2, "close save  error = %s\n", strerror(errno));
	wait_zombies(head);
	return (1);
}

int			check_pipes(t_ast *ast, t_lst_head *head)
{
	t_list_d	*cur;
	t_pipe		*pr;
	t_pipe		*pl;

	cur = head->middle;
	pr = (cur != NULL) ? cur->data : NULL;
	pl = (cur && cur->prev) ? cur->prev->data : NULL;
	if (pr && !pl)
		p_right(pr, ast, head);
	else if (pr && pl)
		p_both(pr, pl, ast, head);
	else if (!pr && pl)
		p_left(pl, ast, head);
	else
		exec_simple_command(ast, head);
	return (1);
}

/*
**	The first time exec_tree is called, we give it our root node as an
**	argument. Depending on the node symbol, it will start the execution of the
**	various commands.
*/

int			exec_tree(t_ast *ast, t_lst_head *head)
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
			if (ft_strequ(token->value, "|"))
				return (exec_pipe(ast, head));
			else if (ft_strequ(token->value, ";"))
				return (semi_colon(ast, head));
			else if (ft_strequ(token->value, "&&"))
				return(logical_and(ast, head));
			else if (ft_strequ(token->value, "||"))
				return (logical_or(ast, head));
		}
		if (ast)
			return (0);
	}
	return (1);
}
