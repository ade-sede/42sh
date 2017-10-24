#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include "libft.h"
#include "exec.h"
#include "line_editing.h"
#include "lexer.h"
#include "parser.h"
#include "failure.h"

/*
** char	*heredoc_get_input(void)
** {
** 	char	*buff;
**
** 	conf_term_canonical();
** 	singleton_line(->heredoc = 1;
** 	load_prompt(singleton_env(), singleton_line(),
** 			"heredoc", "heredoc> ");
** 	buff = line_editing_get_input(singleton_line(), singleton_hist());
** 	conf_term_normal();
** 	singleton_line()->heredoc = 0;
** 	return (buff);
** }
*/

static int	heredoc(int io_number, char *poem, t_list **redir_stack)
{
	int		*fd;

	fd = ft_memalloc(sizeof(*fd) * 2);
	if (io_number == -1)
		io_number = 0;
	if (pipe(fd) == -1)
		return (investigate_error(1, "heredoc", NULL, 0));
	write(fd[WRITE_END], poem, ft_strlen(poem));
	if (close(fd[WRITE_END]) < 0)
		return (investigate_error(1, "close", NULL, 0));
	push_dup(io_number, fd[READ_END], FALSE, redir_stack);
	free(fd);
	return (1);
}

int			exec_heredoc(t_list *child_list, t_list **redir_stack)
{
	char		*poem;
	int			io_number;
	t_ast		*child_node;
	int			here_flag;

	here_flag = FALSE;
	io_number = -1;
	while (child_list)
	{
		child_node = child_list->data;
		if (child_node->token->id == TK_IO_NUMBER)
			io_number = ft_atoi(child_node->token->value);
		if (child_node->token->id == TK_HERE)
		{
			here_flag = TRUE;
			poem = child_node->heredoc_content;
		}
		child_list = child_list->next;
	}
	if (!here_flag)
		return (-1);
	return (heredoc(io_number, child_node->heredoc_content, redir_stack));
}
