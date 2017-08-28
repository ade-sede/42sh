/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comple_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 05:07:29 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/28 20:02:36 by vcombey          ###   ########.fr       */
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

void	comple_handle_sigint(int signum)
{
	t_comple	*c;

	c = singleton_comple();
	comple_clear(*c);
	put_termcap("up");
	comple_free(*c);
	singleton_line()->completion = 0;
	edit_set_signals();
	edit_refresh(singleton_line());
	(void)signum;
}

void	comple_set_comple_signum(int num)
{
	singleton_comple()->signum = num;
}

void	comple_set_signals(void)
{
	signal(SIGINT, comple_handle_sigint);
	signal(SIGWINCH, comple_handle_sigwinch);
}
