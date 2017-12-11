/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_options.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seddaoud <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/11 16:16:04 by seddaoud          #+#    #+#             */
/*   Updated: 2017/12/11 16:16:05 by seddaoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "read.h"
#include "builtin.h"
#include "libft.h"
#include "t_env.h"
#include "failure.h"
#include "exec.h"

static char	parse_delim(char *arg, t_read *options, char ***args)
{
	if (*++arg)
		options->delim = *arg;
	else if (*(*args + 1))
		options->delim = **++*args;
	else
		return (errno = 22) ? 2 : 2;
	return (0);
}

static char	parse_nchars(char *arg, t_read *options, char ***args)
{
	int nchars;

	nchars = 0;
	if (*++arg)
	{
		while (*arg >= '0' && *arg <= '9')
			nchars = nchars * 10 + *arg++ - '0';
		if (*arg)
			return (errno == 22) ? 1 : 1;
	}
	else if (*++*args)
	{
		arg = **args;
		while (*arg >= '0' && *arg <= '9')
			nchars = nchars * 10 + *arg++ - '0';
		if (*arg)
			return (errno = 22) ? 1 : 1;
	}
	else
		return (errno = 22) ? 2 : 2;
	options->nchars = nchars;
	return (0);
}

static char	parse_fd(char *arg, t_read *options, char ***args)
{
	int	fd;

	fd = 0;
	if (*++arg)
	{
		while (*arg >= '0' && *arg <= '9')
			fd = (fd * 10) + (*arg++ - '0');
		if (*arg)
			return (errno = 22) ? 1 : 1;
	}
	else if (*++*args)
	{
		arg = **args;
		while (*arg >= '0' && *arg <= '9')
			fd = (fd * 10) + *arg++ - '0';
		if (*arg)
			return (errno = 22) ? 1 : 1;
	}
	else
		return (errno = 22) ? 2 : 2;
	if (!((options->fd = fd) > -1 && fd < 3))
		return (errno = 9) ? 1 : 1;
	else
		return (EXIT_SUCCESS);
}

static char	parse_prompt(char *arg, t_read *options, char ***args)
{
	char	*word;

	word = ft_strnew(1);
	if (*++arg)
		while (*arg)
			ft_strpush(&word, *arg++);
	else if (*++*args)
	{
		arg = **args;
		while (*arg)
			ft_strpush(&word, *arg++);
	}
	else
	{
		free(word);
		return (errno = 22) ? 2 : 2;
	}
	options->prompt = word;
	return (0);
}

char		parse_read(char *arg, t_read *options, char ***args)
{
	char	status;

	status = EXIT_SUCCESS;
	while (*arg)
	{
		if (*arg == 'r')
			options->flags |= R;
		else if (*arg == 's')
			options->flags |= S;
		else if (*arg == 'd')
			status = parse_delim(arg, options, args);
		else if (*arg == 'n')
			status = parse_nchars(arg, options, args);
		else if (*arg == 'p')
			status = parse_prompt(arg, options, args);
		else if (*arg == 'u')
			status = parse_fd(arg, options, args);
		else
			break ;
		arg++;
	}
	return (failure_read(status, arg));
}
