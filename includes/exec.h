/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:59:06 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/20 12:22:18 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "env.h"
# include "lexer.h"
# include "parser.h"

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
** TODO
**	The array is then sent to execution routines where the following occures:
**	- Try to execute the command as a builtin (by matching it to the list of
**	existing builtins). If this step is a success, execution is over.
**	- If the command is not a builtin, look for the first matching binary in
**	the PATH
**	- A pipe is created, 
**	- Uses fork to create child process, where the binary will be executed.
**	This child process is given
**
**	When execution is over, to the variable env->previous_exit is assigned the
**	return value of the execution.
*/

/*
** In exec_bin.c
*/

int				fork_exec_bin(t_env *env, const char **argv);

/*
** In main_loop.c
*/

void			exec(t_env *env, const char **argv);
void			main_loop(t_env *env);

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

void			exec_tree(t_ast *ast);

/*
** In exec_simple_commands.c
*/

void			exec_simple_command(t_ast *ast);

/*
** In redir.c
*/

void			exec_redir(t_ast *ast, t_list **redir_stack);
void			close_redir(t_list *redir_stack);
void			file_redir(int io_number, char *target, \
		t_list **redir_stack, t_token_id id);

typedef struct	s_redir
{
	int			id;
	void		(*f)(int, char*, t_list**, t_token_id);
}				t_redir;
#endif
