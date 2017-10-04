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

/* char	*heredoc_get_input(void) */
/* { */
/* 	char	*buff; */

/* 	conf_term_canonical(); */
/* 	singleton_line()->heredoc = 1; */
/* 	load_prompt(singleton_env(), singleton_line(), \ */
/* 			"heredoc", "heredoc> "); */
/* 	buff = line_editing_get_input(singleton_line(), singleton_hist()); */
/* 	conf_term_normal(); */
/* 	singleton_line()->heredoc = 0; */
/* 	return (buff); */
/* } */

int		heredoc(int io_number, char *poem, t_list **redir_stack)
{
	int		*fd;

	fd = ft_memalloc(sizeof(*fd) * 2);
	if (io_number == -1)
		io_number = 0;
	if (pipe(fd) == -1)
		return (investigate_error("heredoc", NULL, 0));
	write(fd[WRITE_END], poem, ft_strlen(poem));
		if (close(fd[WRITE_END]) < 0)
			return (investigate_error("close", NULL, 0));
		push_dup(io_number, fd[READ_END], FALSE, redir_stack);
	free(fd);
	return (1);
}
