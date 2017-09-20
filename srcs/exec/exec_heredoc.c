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

char	*heredoc_get_input(void)
{
	char	*buff;

	conf_term_canonical();
	singleton_line()->heredoc = 1;
	load_prompt(singleton_env(), singleton_line(), \
			"heredoc", "heredoc> ");
	buff = line_editing_get_input(singleton_line(), singleton_hist());
	conf_term_normal();
	singleton_line()->heredoc = 0;
	return (buff);
}

int		heredoc(int io_number, char *target, t_list **redir_stack, \
		t_token_id id)
{
	int		*fd;
	char	*buff;

	buff = NULL;
	fd = ft_memalloc(sizeof(*fd) * 2);
	(void)id;
	if (io_number == -1)
		io_number = 0;
	if (pipe(fd) == -1)
		return (investigate_error("heredoc", NULL, 0));
	else
	{
		while (1)
		{
			buff = heredoc_get_input();
			if (ft_strequ(buff, target) || ft_strchr(buff, 4))
				break ;
			write(fd[WRITE_END], buff, ft_strlen(buff));
			write(fd[WRITE_END], "\n", 1);
		}
		if (close(fd[WRITE_END]) < 0)
			return (investigate_error("close", NULL, 0));
		push_dup(io_number, fd[READ_END], FALSE, redir_stack);
	}
	free(fd);
	return (1);
}
