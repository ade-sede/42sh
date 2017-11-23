#include "expand.h"
#include "libft.h"
#include "exec.h"

static void		exec_comm_child(char *comm, int *fildes, int no_showerr)
{
	int		fd;

	if (fildes[1] != STDOUT_FILENO)
	{
		dup2(fildes[1], STDOUT_FILENO);
		close(fildes[1]);
	}
	if (no_showerr > 0)
	{
		close(STDERR_FILENO);
		fd = open("/dev/null", O_WRONLY);
		if (fd >= 0 && fd != STDERR_FILENO)
		{
			dup2(fd, STDERR_FILENO);
			close(fd);
		}
	}
	close(fildes[0]);
	singleton_jc()->shell_is_interactive = 0;
	lex_and_parse(NULL, comm, 0);
	exit(1);
}

int				exec_comm(char *comm, t_expand *exp, int quoted)
{
	int		buflen;
	int		fildes[2];
	char	buffer[BUFSIZE];
	pid_t	pid;
	t_word	value;

	w_newword(&value);
	if (!comm || !*comm)
		return (0);
	p_pipe(fildes);
	pid = p_fork();
	if (pid == 0)
		exec_comm_child(comm, fildes, exp->flag & NO_SHOW_ERROR);
	close(fildes[1]);
	fildes[1] = -1;
	waitpid(pid, &buflen, 0);
	while ((buflen = read(fildes[0], buffer, BUFSIZE)))
	{
		w_addmem(&value, buffer, buflen);
	}
	handle_fieldsplitting(value.str, exp, quoted);
	w_free(&value);
	return (0);
}
