/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   job_background.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:36 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:21 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "failure.h"
#include "job_control.h"

int		put_job_in_background(t_job *j, int cont)
{
	format_job_info_process(j, "launched");
	if (cont)
		if (kill(-j->pgid, SIGCONT) < 0)
			investigate_error(1, "kill (SIGCONT)", NULL, 0);
	return (EXIT_SUCCESS);
}
