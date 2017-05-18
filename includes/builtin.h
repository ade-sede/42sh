# ifndef BUILTIN_H
# define BUILTIN_H

int	builtin_unsetenv(t_env *env, const char **argv);
int	builtin_setenv(t_env *env, const char **argv);
int	builtin_exit(t_env *env, const char **argv);
int	builtin_env(t_env *env, const char **argv);
int	builtin_cd(t_env *env, const char **argv);
int	exec_builtin(t_env *env, const char **argv);

typedef struct	s_builtin
{
	const char	*key;
	int		(*f)(t_env*, const char**);
}			t_builtin;

#endif
