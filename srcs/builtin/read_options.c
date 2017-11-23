#include "read.h"
#include "builtin.h"
#include "libft.h"
#include "t_env.h"
#include "failure.h"
#include "exec.h"

static char		parse_delim(char *arg, t_read *options, char ***args)
{
	if (*++arg)
		options->delim = *arg;
	else if (*(*args + 1))
		options->delim = **++*args;
	else
		return (0);
	return (1);
}

static char		parse_nchars(char *arg, t_read *options, char ***args)
{
	int		nchars;

	nchars = 0;
	if (*++arg)
	{
		while (*arg >= '0' && *arg <= '9')
			nchars = nchars * 10 + *arg++ - '0';
		if (*arg)
			return (0);
	}
	else if (*++*args)
	{
		arg = **args;
		while (*arg >= '0' && *arg <= '9')
			nchars = nchars * 10 + *arg++ - '0';
		if (*arg)
			return (0);
	}
	else
		return (0);
	options->nchars = nchars;
	return (1);
}

static char		parse_fd(char *arg, t_read *options, char ***args)
{
	int		fd;

	fd = 0;
	if (*++arg)
	{
		while (*arg >= '0' && *arg <= '9')
			fd = (fd * 10) + (*arg++ - '0');
		if (*arg)
			return (0);
	}
	else if (*++*args && (arg = **args))
	{
		while (*arg >= '0' && *arg <= '9')
			fd = (fd * 10) + *arg++ - '0';
		if (*arg)
			return (0);
	}
	else
		return (0);
	if (fd > -1 && fd < 3)
		return (1);
	if (fcntl((options->fd = fd), F_GETFL) != -1 && fcntl(fd, F_GETFD) != -1 &&
			errno != EBADF)
		return (1);
	return (2);
}

static char		parse_prompt(char *arg, t_read *options, char ***args)
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
		return (0);
	}
	options->prompt = word;
	return (1);
}

char			parse_read(char *arg, t_read *options, char ***args)
{
	char	status;

	status = -1;
	while (*arg && status == -1)
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
		arg++;
	}
	if (!status)
	{
		return_failure("syntax error near ", arg - 2);
		return_failure("usage : ", USG);
	}
	return (!status ? 0 : 1);
}
