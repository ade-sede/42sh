#ifndef BUILTIN_H
# define BUILTIN_H
# include "env.h"
# include "history.h"
# include "fcntl.h"

/*
** In unsetenv.c
*/

int				builtin_unsetenv(t_env *env, const char **argv);

/*
** In setenv.c
*/

int				builtin_setenv(t_env *env, const char **argv);

/*
** In env.c
*/

int				builtin_env(t_env *env, const char **argv);

/*
** In env.c
*/

int				builtin_exit(t_env *env, const char **argv);

/*
** In cd.c
*/

int				builtin_cd(t_env *env, const char **argv);

/*
** In exec_builtin.c
*/

int				exec_builtin(t_env *env, const char **argv);

/*
** In echo.c
*/

int				builtin_echo(t_env *env, const char **argv);

/*
** In alias.c
*/

int				builtin_alias(t_env *env, const char **argv);
int				builtin_unalias(t_env *env, const char **argv);
t_list			*find_alias(t_list *alias, const char *argv, size_t len);

/*
** In unset.c
*/

int				builtin_unset(t_env *env, const char **argv);

/*
** In set.c
*/

int				builtin_set(t_env *env, const char **argv);
int				match_name_option(const char *argv);
void			print_current_option(t_env *env);
void			print_all_option(t_env *env);

/*
** In file history.c
*/

typedef struct	s_history_opt
{
	const char	*key;
	const char	**(*f)(t_hist*, const char **argv, int *error);
}				t_history_opt;

int				builtin_history(t_env *env, const char **argv);
const char		**handle_options(t_hist *h, const char **argv, int *ret);
int				parse_options(t_hist *h, const char **argv);

/*
** 	In file history_handle_options.c
*/

const char		**handle_r(t_hist *h, const char **argv, int *error);

/*
**	The builtin struct, holding a key (name of the builtin)
**	and the corresponding function
*/

typedef struct	s_builtin
{
	const char	*key;
	int			(*f)(t_env*, const char**);
}				t_builtin;

void		*get_exec_builtin(const char *argv);
#endif
