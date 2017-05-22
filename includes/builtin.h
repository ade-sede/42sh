# ifndef BUILTIN_H
# define BUILTIN_H

/*
** In unsetenv.c
*/

int	builtin_unsetenv(t_env *env, const char **argv);

/*
** In setenv.c
*/

int	builtin_setenv(t_env *env, const char **argv);

/*
** In env.c
*/

int	builtin_env(t_env *env, const char **argv);

/*
** In env.c
*/

int	builtin_exit(t_env *env, const char **argv);

/*
** In cd.c
*/

int	builtin_cd(t_env *env, const char **argv);

/*
** In exec_builtin.c
*/

int	exec_builtin(t_env *env, const char **argv);

/*
** In echo.c
*/

int	builtin_echo(t_env *env, const char **argv);

typedef struct	s_builtin
{
	const char	*key;
	int		(*f)(t_env*, const char**);
}			t_builtin;

#endif
