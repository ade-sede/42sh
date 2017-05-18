# ifndef BUILTIN_H
# define BUILTIN_H

int		exec_builtin(t_env *env, char **av)

typedef struct	s_builtin
{
	const char	*key;
	int		(*f)(t_env*, char**);
}			t_builtin;

#endif
