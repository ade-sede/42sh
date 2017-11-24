/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   layer_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:04 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hash_table.h"
#include "expand.h"
#include "builtin.h"
#include "failure.h"
#include "local.h"
#include "job_control.h"
#include "exec.h"

int		layer_exec(t_env *env, char **av)
{
	int			exit_status;
	t_lst_func	*fct;

	fct = NULL;
	exit_status = EXIT_SUCCESS;
	if ((fct = get_function(env, av[0])))
		exit_status = exec_function(fct->fct_body, av);
	else if (get_exec_builtin(av[0]))
		exit_status = exec_builtin(env, (const char **)av);
	else
		exec_bin(env, (const char **)av);
	return (exit_status);
}
