static void	exec_comm_child (char *comm, int *fildes, int showerr,
		int noexec)
{
	if (fildes[1] != STDOUT_FILENO)
	{
		__dup2 (fildes[1], STDOUT_FILENO);
		__close (fildes[1]);
	}
	else
		/* Reset the close-on-exec flag (if necessary).  */
		__fcntl (fildes[1], F_SETFD, 0);

	/* Redirect stderr to /dev/null if we have to.  */
	if (showerr == 0)
	{
		struct stat64 st;
		int fd;
		close (STDERR_FILENO);
		fd = open (_PATH_DEVNULL, O_WRONLY);
		if (fd >= 0 && fd != STDERR_FILENO)
		{
			dup2 (fd, STDERR_FILENO);
			close (fd);
		}
		unsetenv ("IFS");
		close (fildes[0]);
		execve (_PATH_BSHELL, (char *const *) args, __environ);
		singleton_jc()->shell_is_interactive = 0;
		lex_and_parse(NULL, comm);
		abort ();
	}
}
/* pwordexp contains NULL if field-splitting is forbidden */
#define bufsize 128

int		exec_comm (char *comm, t_word *word,
		t_expand *exp, const char *ifs)
{
	int fildes[2];
	int buflen;
	int i;
	int status = 0;
	size_t maxnewlines = 0;
	char buffer[bufsize];
	pid_t pid;
	int noexec = 0;
	t_word	value;

	w_newword(&value);
	if (!comm || !*comm)
		return 0;
	ppipe (fildes);
	pid = pfork();
	if (pid == 0)
		exec_comm_child (comm, fildes, noexec ? 0 : flags & WRDE_SHOWERR, noexec);
	close (fildes[1]);
	fildes[1] = -1;
	while (1)
	{
		if ((buflen = read (fildes[0], buffer, bufsize))) < 1)
		{
			/* If read returned 0 then the process has closed its
			   stdout.  Don't use WNOHANG in that case to avoid busy
			   looping until the process eventually exits.  */
			if (waitpid (pid, &status, buflen == 0 ? 0 : WNOHANG)) 
				continue;
			if ((buflen = read (fildes[0], buffer, bufsize))) < 1)
				break;
		}
		maxnewlines += buflen;
		w_addmem (&value, buffer, buflen);
	}
	handle_fieldsplitting(value.str, g_word, word,	
			exp, ifs, quoted);
	w_free(&value);
}
