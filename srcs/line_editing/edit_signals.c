/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:35 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "line_editing.h"
#include <signal.h>

int		g_abort_opening;

void	edit_handle_sigwinch(int signum)
{
	singleton_comple()->ws_col = get_ws_col();
	singleton_line()->ws_col = get_ws_col();
	(void)signum;
}

void	edit_handle_sigint_open(int signum)
{
	history_init(singleton_hist());
	move_cursor_lastline(singleton_line());
	edit_line_init(singleton_line(), &edit_set_signals_open);
	ft_putchar_fd('\n', 2);
	put_prompt(singleton_line());
	(void)signum;
}

void	edit_set_signals_open(void)
{
	signal(SIGINT, edit_handle_sigint_open);
	signal(SIGWINCH, edit_handle_sigwinch);
}

void	edit_set_signals_reopen(void)
{
	struct sigaction new_action;

	new_action.sa_handler = edit_handle_sigint_reopen;
	sigemptyset(&new_action.sa_mask);
	new_action.sa_flags = 0;
	sigaction(SIGINT, &new_action, NULL);
	signal(SIGWINCH, edit_handle_sigwinch);
}

void	edit_handle_sigint_reopen(int signum)
{
	move_cursor_lastline(singleton_line());
	g_abort_opening = 1;
	(void)signum;
}
