#include "exec.h"
#include "expand.h"

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
#include "failure.h"
int	exec_io_redirect(t_ast	*ast, t_list **redirect_list)
{
	int			io_number;
	int			(*f)(int, char*, t_list**, int);
	char		*filename;
	int	id;
	t_ast		*io_file = NULL;
	t_ast		*io_here = NULL;
	int			mypipe[2];
	char		**expanded_filename;

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
		filename = io_file->child[1]->child[0]->token->value;

		expanded_filename = word_expansion(filename, NO_FIELDSPLITING);
		//fprintf(stderr, "[filename vaut %s]\n", expanded_filename[0]);
		//fprintf(stderr, "[return vaut %d]\n", f(io_number, filename, redirect_list, id));
		//fprintf(stderr, "[return vaut %d]\n", f(io_number, filename, redirect_list, id));
		if (!(f(io_number, expanded_filename[0], redirect_list, id)))
		{
			ft_arraydel(&expanded_filename);
			return (0);
		}
		ft_arraydel(&expanded_filename);

	}
	if (is_symb(ast->child[0], IO_HERE))
		io_here = ast->child[0];
	else if (is_symb(ast->child[1], IO_HERE))
		io_here = ast->child[1];
	if (io_here)
	{
		/* create the pipe */
		if (pipe(mypipe) == -1)
		{
			investigate_error(1, "pipe", "pipe failed",
						EXIT_FAILURE);
			return 0;
		}
		//pipe(mypipe);
		ft_putstr_fd(io_here->heredoc, mypipe[1]);
		close(mypipe[1]);
		push_dup(io_number == -1 ? STDIN_FILENO : io_number, mypipe[0], FALSE, redirect_list);
	}
	return 1;
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
