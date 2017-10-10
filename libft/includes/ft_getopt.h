#ifndef MY_GETOPT_H
# define MY_GETOPT_H

/*
** http://manpagesfr.free.fr/man/man3/getopt.3.html
** getopt is a standard POSIX function for parsing command line arguments,
** getopt_long is more powerfull with the implementation of long arguments
** like --savepoint=/home/toto for exemple, it is considered like a GNU
** extension.
** If there are no more option characters, getopt() returns -1. Then optind
** is the index in argv of the first argv-element that is not an option.
** optarg, optind, opterr and optopt are originally extern variables, bundled
** in a structure.
*/

/*
** https://www.gnu.org/software/libc/manual/html_node/Using-Getopt.html
** opterr:
** If the value of this variable is nonzero, then getopt prints an error
** message to the standard error stream if it encounters an unknown option
** character or an option with a missing required argument. This is the default
** behavior. If you set this variable to zero, getopt does not print any
** messages, but it still returns the character ? to indicate an error.
** optopt:
** When getopt encounters an unknown option character or an option with a
** missing required argument, it stores that option character in this variable.
** You can use this for providing your own diagnostic messages
** optind:
** This variable is set by getopt to the index of the next element of the argv
** array to be processed. Once getopt has found all of the option arguments,
** you can use this variable to determine where the remaining non-option
** arguments begin. The initial value of this variable is 1.
** optarg:
** This variable is set by getopt to point at the value of the option argument,
** for those options that accept arguments.
*/

/*
** PRIVATE: int optchar;				next chat in same argv
** PRIVATE: char first_char;			norme convenience
*/

struct		s_opt_extern
{
	char	*optarg;
	int		optind;
	int		opterr;
	int		optopt;
	int		optchar;
	char	first_char;
};

int			my_getopt(int argc, char *const argv[], const char *optstring,
			struct s_opt_extern *opt_extern);

void		init_getopt_extern(struct s_opt_extern *opt_extern, int errlog);

#endif
