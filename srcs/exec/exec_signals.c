/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_signals.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/08/27 04:40:02 by vcombey           #+#    #+#             */
/*   Updated: 2017/08/27 04:40:06 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"

void	nothing(int signum)
{
	(void)signum;
}

void	no_handle_signals(void)
{
	signal(SIGINT, nothing);
}
