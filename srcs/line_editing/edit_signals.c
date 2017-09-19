/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:50 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:27 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"
#include "history.h"
#include "line_editing.h"

void	edit_handle_sigwinch(int signum)
{
	singleton_comple()->ws_col = get_ws_col();
	singleton_line()->ws_col = get_ws_col();
	(void)signum;
}

void	edit_handle_sigint(int signum)
{
	history_init(singleton_hist());
	move_cursor_lastline(singleton_line());
	edit_line_init(singleton_line());
	ft_putchar_fd('\n', 2);
	put_prompt(singleton_line());
	(void)signum;
}

void	edit_set_signals(void)
{
	signal(SIGINT, edit_handle_sigint);
	signal(SIGWINCH, edit_handle_sigwinch);
}
