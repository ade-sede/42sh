/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_signal_dfl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:40:47 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:40:58 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_signal.h"

void	all_signal_dfl(void)
{
	int		x;

	x = 0;
	while (x < 31)
	{
		if (x != SIGINT && x != SIGSTOP && x != SIGCHLD && x != SIGWINCH &&
				x != SIGSEGV)
			signal(x, SIG_DFL);
		x++;
	}
}
