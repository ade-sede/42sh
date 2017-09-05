#ifndef EXEC_H
# define EXEC_H
# include "env.h"
# include "lexer.h"
# include "parser.h"
# include "history.h"
# include "line_editing.h"

/*
**	After lexing and parsing, an AST is created.  If complexe commands are
**	found at the top of the tree, the simple commands they contain are executed
**	depending on the operator of the complexe command.
**	When simple commands are executed, the following operations occure :
**	- Treatment of command prefix ( mainly variable assignement)
**	- The cmd name and all of its suffix are appended to an array.
**	- Every redirection we found in the tree is treated. Informations about the
**	redirections are kept in a list, allowing us to restore the original FDs
**	when all operations are over. The list's data is a malloc'ed int array of
**	size 2, where index 0 contains the original FD, and 1 the new file it is
**	mapped to.
**
**	TODO
**	The array is then sent to execution routines where the following occures:
**	- Try to execute the command as a builtin (by matching it to the list of
**	existing builtins). If this step is a success, execution is over.
**	- If the command is not a builtin, look for the first matching binary in
**	the PATH
**
**	When execution is over, to the variable env->previous_exit is assigned the
**	return value of the execution.
*/

/*
**	About pipes !
**
** 	Consider a pipeline such as this one : `command1 | command2 | command3'
** 	The first pipe is referenced as pipe1, and the second as pipe2.
** 	What happens ? :
**	- A pipe is created. Command1's STDOUT will be replaced by pipe1[WRITE_END].
**	Command2's STDIN will be replaced by pipe1[READ_END] and Command2's STDOUT
**	will be replaced by pipe2[WRITE_END]. Command3's STDIN will be replaced by
**	pipe2[READ_END] and its STDOUT should not be touched.
*/

/*
**	Upon reading the tree, a stack (t_list_d*) of pipes  will be created, and
**	sent to all related fuction calls.
**	- If the simple command is not related to a pipeline, t_list->data == NULL
**	- Otherwise, t_list->data will point to an array of int, allocated by
**	malloc, and of size3. This array will be given to pipe(2), making array[0]
**	and array[1] a pipe. array[2] will be used to store the position of the
**	command : Is it on the write side (array[2] == 1) or on the read side
**	(array[2] == 0) ?
**	When both array[0] and array[1] have been treated, list goes to the next
**	node.
**	We can identify the different cases:
**	array = list->data;
**	if (!array)
**		list->next;
**	else if (array[2] == 1) // We're on the write side of the current pipe {
**	dup2(array[WRITE_END], STDOUT) // DONT FORGET TO SAVE STDOUT with dup if
**	(list->prev != NULL) // Theres a piped command before us, and we're on its
**	read side.  dup2(array[READ_END], STDIN) // DONT FORGET TO SAVE STDIN with
**	dup } else if (array[2] == 2) { dup2(array[READ_END], STDIN) // DONT FORGET
**	TO SAVE STDIN with dup if (list->next != NULL) // Theres a piped command in
**	front of us, we're on its write side.  dup2(array[WRITE_END], STDOUT) //
**	DONT FORGET TO SAVE STDOUT with dup
**		list->next;
**	}
*/

/*
**	Stack of pipes (t_list_d*)
**
** array = list->data
**	if (array)
**	{
**		if (prev->data == NULL) // Gauche du pipe
**				We're on write side.
**		if (prev->data != NULL) // Pipe on our left -> we're in the middle
**				Both side
**	}
**	if (!array)
**	{
**		array = prev->data;
**		if (array == NULL)	// Irrelevant
**			;
**		if (array != NULL)
**				Read side of the pipe ( and end of the pipeline);
**	}
*/

/*
**	Cur is the node representing the separator at the right of the current command.
**	p_right != NULL if the command is before a pipe.
**	p_left != NULL if the command is after a pipe.
*/

/*
**	Defines for an easier use of the pipe function.
*/

# define READ_END 0
# define WRITE_END 1

/*
** In exec_bin.c
*/

int				fork_exec_bin(t_env *env, const char **argv, t_lst_head *head);

/*
** In main_loop.c
*/

void			exec(t_env *env, const char **argv, t_lst_head *head);
void			main_loop(t_env *env);
char			*line_editing_get_input(t_env *env, t_line *line, t_hist *hist);

/*
** In param_expansion.c
*/

void			parameter_expansion(t_env *env, t_token *token);

/*
** In word_expand.
*/

void			exec_expand(t_token *token);

/*
** In tild_expansion.c
*/

void			tild_expand(t_env *env, t_token *token);

/*
** In exec_tree.c
*/

int				end_branch(int error, t_ast *ast);
int				exec_tree(t_ast *ast, t_lst_head *head);
t_ast			*flush_tree(t_ast *ast);

/*
** In exec_simple_commands.c
*/

void			exec_simple_command(t_ast *ast, t_lst_head *head);

/*
** In exec_operator.c
*/

int				logical_or(t_ast *ast, t_lst_head *head);
int				semi_colon(t_ast *ast, t_lst_head *head);
int				logical_and(t_ast *ast, t_lst_head *head);

/*
** In redir.c
*/

void			append_redir(t_ast **root, t_list **token_list);
void			heredoc(int io_number, char *target, t_list **redir_stack, \
		t_token_id id);
void			exec_dup(int io_number, int target_fd, int natural_fd, \
		t_list **redir_stack);
void			exec_redir(t_list *child_list, t_list **redir_stack);
void			close_redir(t_list *redir_stack);
void			file_redir(int io_number, char *target, \
		t_list **redir_stack, t_token_id id);
void			merge_fd(int io_number, char *target, t_list **redir_stack, \
		t_token_id id);
int				redir_open_file(char *target, t_token_id id);

typedef struct	s_redir
{
	int			id;
	void		(*f)(int, char*, t_list**, t_token_id);
}				t_redir;

void			no_handle_signals(void);
#endif
