char	*expand_backquotes(char *value)
{
	char	*res;
	pid_t	pid;
	int		pipe[2];

	pid = fork();
	res = ft_strnew(1);
	value = remove_quote(value);
	if (pid == 0)
	{
		dup2(pipe[1], STDOUT_FILENO);
		close(pipe[1]);
		singleton_jc()->shell_is_interactive = 0;
		lex_and_parse(NULL, value);
		exit(0);
	}
	else
	{
		while (read(pipe[0], &buff, 100))
			res = ft_strjoin(res, buff);
	}
	return (res);
}
