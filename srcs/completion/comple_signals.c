/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comple_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/26 21:13:27 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/26 23:27:18 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"
#include "line_editing.h"
#include <signal.h>

void	comple_handle_sigwinch(int signum)
{
	t_comple	*c;

	c = singleton_comple();
	edit_handle_sigwinch(0);
	put_termcap("cd");
	comple_init_winch(c);
	comple_refresh(singleton_line(), *c);
	(void)signum;
}

void	comple_handle_sigint(t_line *line, t_comple *c)
{
	comple_clear(*c);
	put_termcap("up");
	comple_free(*c);
	(void)line;
}

void	comple_set_comple_signum(int num)
{
	singleton_comple()->signum = num;
}

void	comple_set_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = comple_set_comple_signum;
	sa.sa_mask = 0;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGWINCH, comple_handle_sigwinch);
}
