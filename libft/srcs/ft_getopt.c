#include "libft.h"
#include "ft_getopt.h"
#include "printf.h"

static int	manage_argument(int argc, char *const argv[],
			const char *optstring, struct s_opt_extern *ext)
{
	if (argv[ext->optind][ext->optchar + 1] == '\0')
	{
		ext->optind++;
		if (ext->optind >= argc)
		{
			ext->optind++;
			if (ext->opterr)
				ft_dprintf(2, "%s: option requires an argument -- '%c'\n",
				argv[0], ext->optopt);
			return ((ext->first_char == ':') ? ':' : '?');
		}
		ext->optarg = argv[ext->optind];
	}
	else
		ext->optarg = &argv[ext->optind][ext->optchar + 1];
	ext->optind++;
	ext->optchar = 1;
	return (*optstring);
}

static void	next_opt(char *const argv[], struct s_opt_extern *ext)
{
	if (argv[ext->optind][ext->optchar + 1] == '\0')
	{
		ext->optind++;
		ext->optchar = 1;
	}
	else
		ext->optchar++;
}

static int	manage_error(char *const argv[], struct s_opt_extern *ext)
{
	ext->optopt = argv[ext->optind][ext->optchar];
	next_opt(argv, ext);
	if (ext->opterr)
		ft_dprintf("%s: invalid option -- '%c'\n", argv[0], ext->optopt);
	return ('?');
}

int			my_getopt(int argc, char *const argv[], const char *optstring,
			struct s_opt_extern *ext)
{
	ext->first_char = *optstring;
	ext->optarg = NULL;
	if (ext->optind >= argc)
		return (-1);
	if (*argv[ext->optind] != '-' || ft_strlen(argv[ext->optind]) == 1)
		return (-1);
	if ((ft_strcmp(argv[ext->optind], "--")) == 0)
	{
		ext->optind++;
		return (-1);
	}
	while (*optstring != '\0')
	{
		if (*optstring != ':' && argv[ext->optind][ext->optchar] == *optstring)
			break ;
		optstring++;
	}
	ext->optopt = *optstring;
	if (*optstring == '\0')
		return (manage_error(argv, ext));
	else if (optstring[1] == ':')
		return (manage_argument(argc, argv, optstring, ext));
	next_opt(argv, ext);
	return (*optstring);
}

void		init_getopt_extern(struct s_opt_extern *opt_extern, int errlog)
{
	opt_extern->optind = 1;
	opt_extern->optopt = 0;
	opt_extern->opterr = (errlog) ? TRUE : FALSE;
	opt_extern->optarg = NULL;
	opt_extern->optchar = 1;
}
