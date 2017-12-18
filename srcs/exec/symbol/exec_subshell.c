/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_subshell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:35 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:10 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "exec.h"

/*
**	subshell         : '(' compound_list ')'
*/

int		exec_subshell(t_ast *ast)
{
	t_job		*new_job;
	t_process	*first_process;
	int			tmp;
	int			ret;

	new_job = job_new();
	first_process = process_new(ast->child[1]);
	new_job->first_process = first_process;
	ft_genlst_pushback((void **)&singleton_jc()->first_job, new_job);
	ret = singleton_jc()->warn_exit;
	singleton_jc()->warn_exit = 0;
	tmp = launch_job(singleton_jc(), new_job, 1);
	singleton_jc()->warn_exit = ret;
	return (tmp);
}
