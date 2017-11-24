/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_substitution.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:01 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

char	*remove_quote(char *str)
{
	char *res;

	if (str[0] == '`')
		res = ft_strsub(str, 1, ft_strlen(str) - 2);
	else if (str[0] == '$')
		res = ft_strsub(str, 2, ft_strlen(str) - 3);
	free(str);
	return (res);
}

char	*command_substitution(char *value)
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
		while (read(pipe[0], &buff, 100))
		{
			res = ft_strjoin(res, buff);
			bzero(buff, 100);
		}
	return (res);
}
