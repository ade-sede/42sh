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

	child = fork();
	if (child == 0)
	{
		dup2(pr->p[WRITE_END], STDOUT_FILENO);
		close(pr->p[READ_END]);
		exec_simple_command(ast, head);
		close(pr->p[WRITE_END]);
		exit(0);
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

	child = fork();
	if (child == 0)
	{
		dup2(pl->p[READ_END], STDIN_FILENO);
		close(pl->p[WRITE_END]);
		dup2(pr->p[WRITE_END], STDOUT_FILENO);
		close(pr->p[READ_END]);
		exec_simple_command(ast, head);
		exit(0);
	}
	else
	{
		close(pl->p[WRITE_END]);
		pr->pid = child;
	}
	return (1);
}



int			p_left(t_pipe *pl, t_ast *ast, t_lst_head *head)
{
	int		save;

	save = dup(STDIN_FILENO);
	dup2(pl->p[READ_END], STDIN_FILENO);
	close(pl->p[WRITE_END]);
	exec_simple_command(ast, head);
	close(pl->p[READ_END]);
	dup2(save, STDIN_FILENO);
	close(save);
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
