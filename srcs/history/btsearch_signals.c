/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btsearch_signals.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 01:27:42 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 01:36:23 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "line_editing.h"
#include <signal.h>
#include <stdio.h>

int		btsearch_handle_sigwinch(t_line *line, t_hist *h)
{
	(void)line;
	(void)h;
	return (1);
}

int		btsearch_handle_sigint(t_line *line, t_hist *h)
{
	btsearch_exit(line, h);
	h->signum = 0;
	ft_strclr(line->buff);
	line->len = 0;
	return (1);
}

void	btsearch_set_btsearch_signum(int num)
{
	singleton_hist()->signum = num;
}

void	btsearch_set_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = btsearch_set_btsearch_signum;
	sa.sa_mask = 0;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
}
