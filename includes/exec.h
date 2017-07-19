/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/22 12:59:06 by ade-sede          #+#    #+#             */
/*   Updated: 2017/07/19 14:15:16 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H
# include "env.h"
# include "lexer.h"
# include "parser.h"

/*
** In exec_bin.c
*/

int		fork_exec_bin(t_env *env, const char **argv);

/*
** In main_loop.c
*/

void	exec(t_env *env, const char **argv);
void	main_loop(t_env *env);

/*
** In param_expansion.c
*/

void	parameter_expansion(t_env *env, t_token *token);

/*
** In word_expand.
*/

void	exec_expand(t_token *token);

/*
** In tild_expansion.c
*/

void	tild_expand(t_env *env, t_token *token);

/*
** In exec_tree.c
*/

void	exec_tree(t_ast *ast);

/*
** In exec_simple_commands.c
*/

void	exec_simple_command(t_ast *ast);
#endif
