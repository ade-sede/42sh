/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fg.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:46 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <unistd.h>
#include "failure.h"
#include "job_control.h"

int		builtin_fg(t_env *env, const char **argv)
{
	t_job_control	*jc;
	t_job			*j;
	int				nbr;

	(void)env;
	j = NULL;
	jc = singleton_jc();
	if (!argv[1])
	{
		if (!(j = ft_genlst_last(jc->first_job)))
			return (investigate_error(1, NULL, "fg: no current job", \
						EXIT_FAILURE));
	}
	else if (argv[1] && !argv[2])
	{
		if (argv[1][0] == '%' && ft_atoi_safe(argv[1] + 1, &nbr))
			j = ft_genlst_get_n(jc->first_job, nbr > 0 ? nbr - 1 : nbr);
	}
	if (!j)
		return (investigate_error(1, NULL, "fg: no such job", EXIT_FAILURE));
	continue_job(j, 1);
	return (EXIT_SUCCESS);
}
