/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seddaoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:16:10 by seddaoud          #+#    #+#             */
/*   Updated: 2017/12/11 16:16:11 by seddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"
#include "libft.h"
#include "failure.h"

static char	valide_argv(char c)
{
	return ((c >= 'a' && c <= 'z')
			|| (c >= 'A' && c <= 'Z')
			|| (c >= '0' && c <= '9')
			|| c == '_') ? 1 : 0;
}

char		read_parse_argv(const char **argv)
{
	int	index;

	while (argv && *argv)
	{
		index = -1;
		while ((*argv)[++index] && valide_argv((*argv)[index]))
			;
		if ((*argv)[index])
		{
			return (investigate_error(1,
						"read: not a valid identifier: ", *argv, 0));
		}
		argv++;
	}
	return (1);
}

char		read_parse_option(t_read *options, const char ***args)
{
	char	*option;
	char	status;

	status = EXIT_SUCCESS;
	while (args && *++*args && ***args == '-' && *(**args + 1))
	{
		option = (char*)**args + 1;
		if (option[0] == '-' && !option[1])
		{
			++*args;
			break ;
		}
		if ((status = parse_read(option, options, (char***)args)))
		{
			ft_strdel(&options->prompt);
			return (status);
		}
	}
	return (status);
}

void		read_backslash(char **line, char **word, char quote)
{
	(*line)++;
	if (quote && **line == 'n')
		ft_strpush(word, '\n');
	if (quote && **line == 't')
		ft_strpush(word, '\t');
	if (quote && **line == 'v')
		ft_strpush(word, '\v');
	if (quote && **line == 'a')
		ft_strpush(word, '\a');
	if (quote && **line == 'b')
		ft_strpush(word, '\b');
	if (quote && **line == 'f')
		ft_strpush(word, '\f');
	if (quote && **line == 'r')
		ft_strpush(word, '\r');
	else
		ft_strpush(word, **line);
	(*line)++;
}

char		failure_read(char status, char *arg)
{
	if (status == 1)
		investigate_error(1, "read", NULL, 1);
	else if ((!status && *arg) || status == 2)
	{
		if (ft_strchr("rsdnpu", *arg))
		{
			return_failure("bad option: -", arg - 1);
			investigate_error(1, "read", NULL, 2);
		}
		else
			return_failure("bad option: -", arg);
		status = investigate_error(1, "usage : ", USG, 2);
	}
	return (status);
}
