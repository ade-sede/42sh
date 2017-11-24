/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_expand.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 18:17:19 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 20:00:57 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "bang.h"
#include "history.h"

static int	numeric_event(const char **source, t_word *event, t_hist *hist)
{
	int	count;

	count = 0;
	if (**source == '!')
	{
		count = -1;
		++(*source);
	}
	else if (**source == '-')
	{
		count = ft_atoi_base((char*)*source, 10);
		++(*source);
		while (ft_isdigit(**source))
			++(*source);
	}
	else
	{
		count = ft_atoi_base((char*)*source, 10);
		while (ft_isdigit(**source))
			++(*source);
	}
	if (read_hist_numeric(count, event, hist))
		return (TRUE);
	return (FALSE);
}

static int	valid_event(const char **source, int *done)
{
	if (ft_strchr("^$*:", **source))
	{
		*done = FALSE;
		return (FALSE);
	}
	else if (**source != '!' && **source != '-' && **source != '#' \
			&& **source != '?' && !ft_isalnum(**source))
		return (TRUE);
	return (FALSE);
}

static int	default_behavior(t_hist *hist, t_word *event)
{
	read_hist_numeric(-1, event, hist);
	return (FALSE);
}

static int	wrapper(const char **source, t_word *event, t_hist *hist, int *done)
{
	*done = FALSE;
	if (**source == '!' || **source == '-' || ft_isdigit(**source))
	{
		*done = TRUE;
		if (numeric_event(source, event, hist))
		{
			w_free(event);
			return (TRUE);
		}
	}
	else if (**source == '?' || ft_isalpha(**source))
	{
		*done = TRUE;
		if (string_event(source, event, hist))
		{
			w_free(event);
			return (TRUE);
		}
	}
	return (FALSE);
}

int			event_expand(const char *s, const char **source, \
		t_word *event, t_hist *hist)
{
	int	ret;
	int	done;

	ret = FALSE;
	done = TRUE;
	w_newword(event);
	ret = valid_event(source, &done);
	if (!done)
		return (default_behavior(hist, event));
	if (ret)
		return (TRUE);
	if (wrapper(source, event, hist, &done))
	{
		return (TRUE);
	}
	if (!done)
	{
		if (*source - s - 1 > 0)
			w_addmem(event, s, *source - s - 1);
		++(*source);
	}
	if (!event->str)
		return (TRUE);
	return (FALSE);
}
