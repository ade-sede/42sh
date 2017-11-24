/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_event.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:36 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:17 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "bang.h"
#include "history.h"

#include <stdio.h>

static int	else_event(const char **source, int *flag, t_word *string_event)
{
	*flag = 2;
	while (**source && !ft_strchr(": 	\n", **source))
	{
		w_addchar(string_event, **source);
		++(*source);
	}
	return (1);
}

int			string_event(const char **source, t_word *event, t_hist *hist)
{
	t_word	string_event;
	int		flag;
	int		err;

	w_newword(&string_event);
	if (**source == '?')
	{
		++(*source);
		flag = 1;
		while (**source && !ft_strchr("?\n", **source))
		{
			w_addchar(&string_event, **source);
			++(*source);
		}
		if (**source == '?')
			++(*source);
	}
	else
		else_event(source, &flag, &string_event);
	err = read_hist_string(flag, string_event, event, hist);
	w_free(&string_event);
	return (err);
}
