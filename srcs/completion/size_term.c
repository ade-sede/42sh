/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 17:53:55 by vcombey           #+#    #+#             */
/*   Updated: 2017/05/22 16:52:30 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <stdio.h>

size_t				get_ws_col(void)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	return (w.ws_col);
}
