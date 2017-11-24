/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_format.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:36 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:22 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"
#include <stdio.h>

int		job_number(t_job *j)
{
	t_job	*first_job;
	int		i;

	i = 1;
	first_job = singleton_jc()->first_job;
	while (first_job && first_job != j)
	{
		i++;
		first_job = first_job->next;
	}
	return (i);
}

void	format_job_info_process(t_job *j, const char *status)
{
	t_process	*p;
	char		job_no[21];
	size_t		job_no_length;

	ft_itoa_word(job_number(j), job_no);
	job_no_length = ft_strlen(job_no);
	if (j->foreground)
		ft_putchar('\n');
	ft_dprintf(2, "[%d]", job_number(j));
	p = j->first_process;
	ft_dprintf(2, " %ld %s: %s%s\n", (long)p->pid, status, p->av, \
			p->next ? " |" : "");
	p = p->next;
	while (p)
	{
		ft_putnstr("                ", job_no_length + 2);
		ft_dprintf(2, " %ld %s: %s%s\n", (long)p->pid, status, p->av, \
				p->next ? " |" : "");
		p = p->next;
	}
}
