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

int			exec_tree(t_ast *ast, t_lst_head *head)
{
	t_token		*token;

	token = NULL;
	if (ast)
	{
		if (ast->symbol == SIMPLE_COMMAND)
		{
			pid_t		child;
			int			*p_right;
			int			*p_left;
			int			save;
			t_list_d	*cur;

			cur = head->middle;
			p_right = (cur != NULL) ? cur->data : NULL;
			p_left = (cur && cur->prev) ? cur->prev->data : NULL;

			if (p_right && p_left) // Between pipes
			{
				child = fork();
				if (child == 0)
				{
					/* Read from the pipe on the left */
					dup2(p_left[READ_END], STDIN_FILENO);
					close(p_left[WRITE_END]);


					/* Write to the next pipe */
					dup2(p_right[WRITE_END], STDOUT_FILENO);
					close(p_right[READ_END]);

					/* char buff[4096]; */
					/* bzero(buff, 4096); */
					/* read(STDIN_FILENO, buff, 4096); */
					/* dprintf(2,"Following is read from the middle command on input\n"MAG"#"CYN"%s"MAG"#\n"RESET, buff); */


					/* Execute the command (execve call) */
					exec_simple_command(ast, head);
					/* int	ret = system("wc -l"); */
					/* dprintf(2, "Ret ="RED"%d\n"RESET, ret); */

					/* write(STDOUT_FILENO, buff, 4096); */
					/* char	buff2[4096]; */
					/* bzero(buff, 4096); */
					/* read(p_right[READ_END], buff2, 4096); */
					/* dprintf(2,"Following is read from the middle command on output\n"MAG"#"CYN"%s"MAG"#\n"RESET, buff2); */

					exit(0);
				}
				else
				{
					close(p_left[WRITE_END]);
				}
			}
			else if (p_right) // If our command is on the left of a pipe (WRITE_END)
			{
				child = fork();
				if (child == 0) // In child process
				{
					/* Write to the pipe to the right */
					dup2(p_right[WRITE_END], STDOUT_FILENO);
					close(p_right[READ_END]); // Looks like its optional

					/* Execute the command (execve call) */
					exec_simple_command(ast, head);
					
					/* All FDs are closed from this process */
					close(p_right[WRITE_END]); // Looks like its optional
					exit(0);
				}
			}
			else if (p_left) // Right of the pipe ; happens in the main process.
			{
				/* Save STD INPUT */
				save = dup(STDIN_FILENO);

				/* Read from the pipe on the left */
				dup2(p_left[READ_END], STDIN_FILENO);
				close(p_left[WRITE_END]);

				/* Execute the command */

				/* char	buff3[4096]; */
				/* bzero(buff3, 4096); */
				/* read(p_left[READ_END], buff3, 4096); */
				/* dprintf(2, "read from the last command\n"MAG"#"CYN"%s"MAG"#\n"RESET, buff3); */

				exec_simple_command(ast, head);

				/* Restore fd 0 as the STD INPUT */
				close(p_left[READ_END]);
				dup2(save, 0);
				close(save);
			}
			else
				exec_simple_command(ast, head);

			/* Command execution is done : move to the next node in the list. */
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
