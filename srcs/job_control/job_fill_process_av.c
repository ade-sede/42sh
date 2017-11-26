/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_fill_process_av.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:36 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:22 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "job_control.h"

t_process	*fill_process_av(t_ast *ast, t_process *process)
{
	int		i;
	t_ast	*child;

	i = 0;
	while (ast && ast->child[i])
	{
		child = ast->child[i];
		if (child && child->token)
			process->av = ft_strjoin3_free(process->av, " ", \
					child->token->value, 4);
		else
			fill_process_av(child, process);
		i++;
	}
	return (process);
}
