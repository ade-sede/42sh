#include "expand.h"
#include "libft.h"
#include "exec.h"

static void	exec_comm_child (char *comm, int *fildes, int showerr)
{
	if (fildes[1] != STDOUT_FILENO)
	{
		dup2 (fildes[1], STDOUT_FILENO);
		close (fildes[1]);
	}
	/* Redirect stderr to /dev/null if we have to.  */
	if (showerr == 0)
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
	lex_and_parse(NULL, comm);
	exit (1);
}
/* pwordexp contains NULL if field-splitting is forbidden */
#define bufsize 128

int		exec_comm (char *comm, t_word *g_word, t_word *word,
		t_expand *exp, const char *ifs, int quoted)
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
//	fprintf(stderr, "cmd substitution {%s}\n", comm);
	p_pipe (fildes);
	pid = p_fork();
	if (pid == 0)
		exec_comm_child (comm, fildes, 1);
	close (fildes[1]);
	fildes[1] = -1;
	waitpid (pid, &status, 0);
	while ((buflen = read (fildes[0], buffer, bufsize)))
	{
		maxnewlines += buflen;
		w_addmem (&value, buffer, buflen);
	}
	handle_fieldsplitting(value.str, g_word, word,	
			exp, ifs, quoted);
	w_free(&value);
	return (0);
}
