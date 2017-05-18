# ifndef BUILTIN_H
# define BUILTIN_H

typedef struct	s_builtin
{
	const char	*key;
	int		(*f)(t_env*, char**);
}			t_builtin;

#endif
