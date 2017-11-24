/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_designator_expand.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 18:31:24 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 18:42:11 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bang.h"
#include "libft.h"
#include "lexer.h"

static int	valid_designator(const char **source, int *done)
{
	if (**source == 0 || ft_strchr(" 	\n", **source))
	{
		*done = FALSE;
		return (FALSE);
	}
	if (**source == ':')
	{
		++(*source);
		if (!ft_strchr("^$-*", **source) && !ft_isdigit(**source))
		{
			--(*source);
			*done = FALSE;
			return (TRUE);
		}
	}
	else if (!ft_strchr("^$-*", **source))
		return (TRUE);
	return (FALSE);
}

static int	default_behavior(t_word *word_designator, t_word event)
{
	if (event.str)
		w_addstr(word_designator, event.str);
	return (FALSE);
}

int			word_designator_expand(const char **source, \
		t_word event, t_word *word_designator)
{
	int	ret;
	int	start;
	int	end;
	int	done;

	start = -3;
	end = -3;
	done = TRUE;
	w_newword(word_designator);
	ret = valid_designator(source, &done);
	if (!done)
		return (default_behavior(word_designator, event));
	if (ret)
		return (TRUE);
	parse_range(source, &start, &end);
	if (extract_words(start, end, event, word_designator))
		return (TRUE);
	return (FALSE);
}
