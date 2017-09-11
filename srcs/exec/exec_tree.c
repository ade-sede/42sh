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

/*
**	Deletes the entire tree, from the given node to the last leaf
*/

t_ast		*flush_tree(t_ast *ast)
{
	t_list	*child_list;
	t_ast	*child_node;

	if (ast)
	{
		child_list = ast->child;
		while (child_list)
		{
			child_node = child_list->data;
			if (child_node)
				flush_tree(child_node);
			child_list = child_list->next;
		}
		free_ast_node(ast);
	}
	return (NULL);
}

/*
** 	List of pipes should be generated during parsing and creation of the tree.
** 	Fork and execute the 1st branch in the child, meanwhile everything keeps going in the parent.
** 	Redirection should occure here, (in the child ?) not at the binary / builtin call time.
*/

static int	exec_pipe(t_ast *ast, t_lst_head *head)
{
	if (exec_tree(ast->child->data, head) == 0)
		exec_tree(ast->child->next->data, head);
	else
	{
		ast->child->data = flush_tree(ast->child->next->data);
		head->middle = head->middle->next;
	}
	return (0);
}

/*
**	The first time exec_tree is called, we give it our root node as an
**	argument. Depending on the node symbol, it will start the execution of the
**	various commands.
*/

int			end_branch(int error, t_ast *ast)
{
	ast = free_ast_node(ast);
	return (error);
}

int			p_right(t_pipe *pr, t_ast *ast, t_lst_head *head)
{
	pid_t		child;

	dprintf(2 ,"in p_right\n");
	child = fork();
	if (child == -1)
	{
		dprintf(2 ,"fork error = %s\n", strerror(errno));
		return (0);
	}
	dprintf(2 ,"errno = %s\n", strerror(errno));
	if (child == 0)
	{
		int ret = close(pr->p[READ_END]);
		dprintf(2 ,"p_right close read-end %d error = %s\n", ret, strerror(errno));
		if ((ret = dup2(pr->p[WRITE_END], STDOUT_FILENO)) == -1)
			dprintf(2 ,"p right dup2 error %d error = %s\n", ret, strerror(errno));
		exec_simple_command(ast, head);
	}
	else
	{
		pr->pid = child;
	}
	return (1);
}

int			p_both(t_pipe *pr, t_pipe *pl, t_ast *ast, t_lst_head *head)
{
	pid_t		child;
		int ret;

	child = fork();
	if (child == -1)
	{
		dprintf(2 ,"fork error = %s\n", strerror(errno));
		return (0);
	}
	if (child == 0)
	{
		dprintf(2 ,"in both\n");
		if ((ret = dup2(pl->p[READ_END], STDIN_FILENO)) == -1)
			dprintf(2 ,"dup2 error %d error = %s\n", ret, strerror(errno));
		ret = close(pl->p[WRITE_END]);
		dprintf(2 ,"p_left close write-end %d error = %s\n", ret, strerror(errno));
		ret = close(pr->p[READ_END]);
		dprintf(2 ,"p_right close read-end %d error = %s\n", ret, strerror(errno));
		if ((ret = dup2(pr->p[WRITE_END], STDOUT_FILENO)) == -1)
			dprintf(2 ,"p right dup2 error %d error = %s\n", ret, strerror(errno));
		exec_simple_command(ast, head);
	}
	else
	{
		ret = close(pl->p[WRITE_END]);
		dprintf(2 ,"p_both close write-end %d error = %s\n", ret, strerror(errno));
		ret = close(pl->p[READ_END]);
		dprintf(2 ,"p_both close read-end %d error = %s\n", ret, strerror(errno));
		pr->pid = child;
	}
	return (1);
}



int			p_left(t_pipe *pl, t_ast *ast, t_lst_head *head)
{
	dprintf(2, RED"%d\n"RESET, errno);
	int		save;
	int ret;

	dprintf(2 ,"in left\n");
	if ((save = dup(STDIN_FILENO)) == -1)
		dprintf(2 ,"dup error %d error = %s\n", save, strerror(errno));
	if ((ret = dup2(pl->p[READ_END], STDIN_FILENO)) == -1)
		dprintf(2 ,"dup2 error %d error = %s\n", ret, strerror(errno));
	ret = close(pl->p[WRITE_END]);
	dprintf(2 ,"p_left close write-end %d error = %s\n", ret, strerror(errno));

	exec_simple_command(ast, head);

	(void)ast, (void)head;
	ret = close(pl->p[READ_END]);
	dprintf(2 ,"p_left close read-end %d error = %s\n", ret, strerror(errno));
	if ((ret = dup2(save, STDIN_FILENO)) == -1)
		dprintf(2 ,"dup2 error %d error = %s\n", ret, strerror(errno));
	ret = close(save);
	dprintf(2 ,"close save %d error = %s\n", ret, strerror(errno));
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
	{
		dprintf(2, "\n\n\n\n");
		p_left(pl, ast, head);
	}
	else
		exec_simple_command(ast, head);
	return (1);
}

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
				exec_pipe(ast, head);
			else if (ft_strequ(token->value, ";"))
				return (end_branch(semi_colon(ast, head), ast));
			else if (ft_strequ(token->value, "&&"))
				return (end_branch(logical_and(ast, head), ast));
			else if (ft_strequ(token->value, "||"))
				return (end_branch(logical_or(ast, head), ast));
		}
		if (ast)
			return (end_branch(0, ast));
	}
	return (1);
}
