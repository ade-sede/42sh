/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 05:08:19 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 05:08:24 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int				exec_builtin(t_env *env, const char **argv, t_lst_head *head);

/*
** In echo.c
*/

int				builtin_echo(t_env *env, const char **argv);

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

#endif
