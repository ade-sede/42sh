/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   jobs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:46 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "printf.h"
#include <unistd.h>
#include "failure.h"
#include "job_control.h"

static void		print_command(t_job *j)
{
	t_process		*p;

	p = j->first_process;
	while (p)
	{
		ft_dprintf(2, "%s %s", p->av, p->next ? "| " : "");
		p = p->next;
	}
}

static void		print_status(t_job *j)
{
	if (job_is_stopped(j))
		ft_dprintf(2, "suspended ");
	else
		ft_dprintf(2, "running   ");
}

int				builtin_jobs(t_env *env, const char **argv)
{
	t_job_control	*jc;
	t_job			*j;
	int				i;

	(void)env;
	(void)argv;
	i = 1;
	jc = singleton_jc();
	j = jc->first_job;
	while (j)
	{
		ft_dprintf(2, "[%d]    ", i);
		print_status(j);
		print_command(j);
		ft_putchar('\n');
		j = j->next;
		i++;
	}
	return (EXIT_SUCCESS);
}
