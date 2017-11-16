#include "expand.h"
#include "libft.h"
#include "exec.h"

static void	exec_comm_child (char *comm, int *fildes, int no_showerr)
{
	if (fildes[1] != STDOUT_FILENO)
	{
		dup2 (fildes[1], STDOUT_FILENO);
		close (fildes[1]);
	}
	/* Redirect stderr to /dev/null if we have to.  */
	if (no_showerr > 0)
	{
		int fd;
		close (STDERR_FILENO);
		fd = open ("/dev/null", O_WRONLY);
		if (fd >= 0 && fd != STDERR_FILENO)
		{
			dup2 (fd, STDERR_FILENO);
			close (fd);
		}
	}
	//unsetenv ("IFS");
	close (fildes[0]);
	singleton_jc()->shell_is_interactive = 0;
//	fprintf(stderr, "exec_comm_child {%s}\n", comm);
	lex_and_parse(NULL, comm, 0); // TODO: attention
	exit (1);
}
/* pwordexp contains NULL if field-splitting is forbidden */
#define bufsize 128

int		exec_comm (char *comm, t_expand *exp)
{
	int fildes[2];
	int buflen;
	int status = 0;
	size_t maxnewlines = 0;
	char buffer[bufsize];
	pid_t pid;
	t_word	value;

	w_newword(&value);
	if (!comm || !*comm)
		return 0;
	//fprintf(stderr, "cmd substitution {%s}\n", comm);
	p_pipe (fildes);
	pid = p_fork();
	if (pid == 0)
		exec_comm_child (comm, fildes, exp->flag & NO_SHOW_ERROR);
	close (fildes[1]);
	fildes[1] = -1;
	waitpid (pid, &status, 0);
	while ((buflen = read (fildes[0], buffer, bufsize)))
	{
		maxnewlines += buflen;
		w_addmem (&value, buffer, buflen);
	}
	//fprintf (stderr, "value cmd subst{%s}\n", value.str);

	handle_fieldsplitting(value.str, exp);
	w_free(&value);
	return (0);
}
