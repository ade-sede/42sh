/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:59:06 by ade-sede          #+#    #+#             */
/*   Updated: 2017/06/27 19:10:41 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/*
** In exec_bin.c
*/

int		fork_exec_bin(t_env *env, const char **argv);

/*
** In main_loop.c
*/

void	main_loop(t_env *env);

/*
** In expand_args.c
*/

void	exec_expand_args(t_env env, char **argv);
#endif
