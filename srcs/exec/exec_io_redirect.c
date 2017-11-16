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

void	exec_io_redirect(t_ast	*ast, t_list **redirect_list)
{
	int			io_number;
	int			(*f)(int, char*, t_list**, int);
	char		*target;
	int	id;
	t_ast		*io_file = NULL;
	t_ast		*io_here = NULL;

	io_number = -1;
	if (is_token(ast->child[0], TK_IO_NUMBER))
		io_number = ft_atoi(ast->child[0]->token->value);
	if (is_symb(ast->child[0], IO_FILE))
		io_file = ast->child[0];
	else if (is_symb(ast->child[1], IO_FILE))
		io_file = ast->child[1];
	if (io_file)
	{
		id = io_file->child[0]->token->id;
		f = get_exec_redir_func(id);
		target = io_file->child[1]->child[0]->token->value;
		f(io_number, target, redirect_list, id);
	}
	if (is_symb(ast->child[0], IO_HERE))
		io_here = ast->child[0];
	else if (is_symb(ast->child[1], IO_HERE))
		io_here = ast->child[1];
//	if (io_here)
	/*
	** creer pipe
	** ecrire ast->heredoc pipe[WRITE_END]
	** push_dup(io_number, pipe[READ_END], FALSE, redirect_list)
	*/
}

/*
**	o_here           : DLESS     here_end
**	                 | DLESSDASH here_end
**	                 ;
**	here_end         : WORD
*/
