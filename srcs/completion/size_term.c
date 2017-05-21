/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_term.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/27 17:53:55 by vcombey           #+#    #+#             */
/*   Updated: 2017/01/27 17:54:51 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include <stdio.h>
#include "ft_ls.h"

int				get_ws_col(void)
{
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	return (w.ws_col);
}
