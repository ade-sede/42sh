/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comple_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 23:19:54 by vcombey           #+#    #+#             */
/*   Updated: 2017/06/08 23:20:13 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"
#include "line_editing.h"
#include <signal.h>
#include <stdio.h>

void	comple_handle_sigwinch(t_line *line, t_comple *c)
{
	//put_termcap("cr");
	//put_termcap("cd");
	//comple_clear(*c());
	comple_init_winch(c);
	comple_clear(*c);
	put_termcap("cl");
	comple_refresh(line, *c);
}

void	comple_handle_sigint(t_line *line, t_comple *c)
{
	//move_cursor_lastline(line);
	//edit_line_init(line);
	comple_clear(*c);
	put_termcap("up");	
	comple_free(*c);
	(void)line;
	//put_prompt(NULL);
}

void	comple_set_comple_signum(signum)
{
	singleton_comple()->signum = signum;
}

void	comple_set_signals(void)
{
	struct sigaction sa;

	sa.sa_handler = comple_set_comple_signum;
	sa.sa_mask = 0;
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);

	//signal(SIGWINCH, comple_set_comple_signum);
	//signal(SIGINT, comple_set_comple_signum);

}
