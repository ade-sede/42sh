/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 23:19:54 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 04:53:14 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"
#include "history.h"
#include "line_editing.h"

void	edit_handle_sigwinch(int signum)
{
	singleton_comple()->ws_col = get_ws_col();
	singleton_line()->ws_col = get_ws_col();
	edit_refresh(singleton_line());
	(void)signum;
}

void	edit_handle_sigint(int signum)
{
	history_init(singleton_hist());
	move_cursor_lastline(singleton_line());
	edit_line_init(singleton_line());
	ft_putchar('\n');
	put_prompt(singleton_line());
	(void)signum;
}

void	edit_set_signals(void)
{
	signal(SIGINT, edit_handle_sigint);
	signal(SIGWINCH, edit_handle_sigwinch);
}
