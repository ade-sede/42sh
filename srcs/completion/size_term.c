/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:47 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:08 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <stdlib.h>

size_t				get_ws_col(void)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	return (w.ws_col);
}

size_t				get_ws_row(void)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	return (w.ws_row);
}
