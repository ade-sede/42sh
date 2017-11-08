#include "job_control.h"

char	*expand_cmd_subst(char *value)
{
	char	*res;
	char	buff[100];
	pid_t	pid;
	int		pipe[2];

	res = ft_strnew(1);
	value = remove_quote(value);
	pipe(pipe);
	pid = fork();
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
		{
			res = ft_strjoin(res, buff);
			bzero(buff, 100);
		}
	}
	return (res);
}
