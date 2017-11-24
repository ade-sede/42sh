/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_io_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:59 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expand.h"
#include "failure.h"
#include "exec.h"

/*
**	io_redirect      :           io_file
**	                 | IO_NUMBER io_file
**	                 |           io_here
**	                 | IO_NUMBER io_here
**	                 ;
**	io_file          : '<'       filename
**	                 | LESSAND   filename
**	                 | '>'       filename
**	                 | GREATAND  filename
**	                 | DGREAT    filename
**	                 | LESSGREAT filename
**	                 | CLOBBER   filename
*/

static int	io_file_f(t_ast *io_file, int io_number, t_list **redirect_list)
{
	int			id;
	char		**expanded_filename;
	char		*filename;
	int			(*f)(int, char*, t_list**, int);

	id = io_file->child[0]->token->id;
	f = get_exec_redir_func(id);
	filename = io_file->child[1]->child[0]->token->value;
	expanded_filename = word_expansion(filename, NO_FIELDSPLITING);
	if (!(f(io_number, expanded_filename[0], redirect_list, id)))
	{
		ft_arraydel(&expanded_filename);
		return (0);
	}
	ft_arraydel(&expanded_filename);
	return (1);
}

static int	io_here_f(t_ast *io_here, int io_number, t_list **redirect_list)
{
	int			mypipe[2];

	if (pipe(mypipe) == -1)
	{
		investigate_error(1, "pipe", "pipe failed", EXIT_FAILURE);
		return (0);
	}
	ft_putstr_fd(io_here->heredoc, mypipe[1]);
	close(mypipe[1]);
	push_dup(io_number == -1 ? STDIN_FILENO : io_number, mypipe[0], FALSE,
			redirect_list);
	return (1);
}

int			exec_io_redirect(t_ast *ast, t_list **redirect_list)
{
	int			io_number;
	t_ast		*io_file;
	t_ast		*io_here;

	io_file = NULL;
	io_here = NULL;
	io_number = -1;
	if (is_token(ast->child[0], TK_IO_NUMBER))
		io_number = ft_atoi(ast->child[0]->token->value);
	if (is_symb(ast->child[0], IO_FILE))
		io_file = ast->child[0];
	else if (is_symb(ast->child[1], IO_FILE))
		io_file = ast->child[1];
	if (io_file && !io_file_f(io_file, io_number, redirect_list))
		return (0);
	if (is_symb(ast->child[0], IO_HERE))
		io_here = ast->child[0];
	else if (is_symb(ast->child[1], IO_HERE))
		io_here = ast->child[1];
	if (io_here && !io_here_f(io_here, io_number, redirect_list))
		return (0);
	return (1);
}

/*
** creer pipe
** ecrire ast->heredoc pipe[WRITE_END]
** push_dup(io_number, pipe[READ_END], FALSE, redirect_list)
*/

/*
**	o_here           : DLESS     here_end
**	                 | DLESSDASH here_end
**	                 ;
**	here_end         : WORD
*/
