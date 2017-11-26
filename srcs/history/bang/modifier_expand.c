/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifier_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:36 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:16 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bang.h"
#include "libft.h"

static int	valid_modifier(const char **source, int *done)
{
	if (**source == ':')
	{
		++(*source);
		if (!**source || !ft_strchr("htreqxsg", **source))
			return (TRUE);
	}
	else
	{
		*done = FALSE;
		return (FALSE);
	}
	return (FALSE);
}

static int	default_behavior(t_word *ret, t_word word_designator)
{
	if (word_designator.str)
		w_addstr(ret, word_designator.str);
	return (FALSE);
}

static int	subroutine(const char **source, struct s_parse_mod *p)
{
	if (**source == 'g' || **source == 's')
	{
		if (substitute(source, p))
			return (TRUE);
	}
	else
		trunc_routines(source, p);
	pop(&p->cache, &p->tmp);
	return (FALSE);
}

static int	apply_modifier(const char **source, struct s_parse_mod *p)
{
	int		done;

	done = TRUE;
	while (**source && done)
	{
		if (**source == 'q' || **source == 'x')
		{
			if (**source == 'q')
				p->quote_mode = 'q';
			else if (**source == 'x')
				p->quote_mode = 'x';
			++(*source);
		}
		else
		{
			if (subroutine(source, p))
				return (TRUE);
		}
		if (valid_modifier(source, &done))
			return (TRUE);
	}
	return (FALSE);
}

int			modifier_expand(const char **source, t_word *ret, \
		t_word word_designator)
{
	int					r;
	int					done;
	struct s_parse_mod	p;

	done = TRUE;
	r = valid_modifier(source, &done);
	if (!done)
		return (default_behavior(ret, word_designator));
	if (r)
		return (TRUE);
	w_newword(ret);
	init_p(&p, word_designator);
	if (apply_modifier(source, &p))
	{
		w_free(&p.cache);
		w_free(&p.tmp);
		return (TRUE);
	}
	if (p.quote_mode)
		apply_quotes(&p);
	if (p.cache.str)
		w_addstr(ret, p.cache.str);
	w_free(&p.cache);
	w_free(&p.tmp);
	return (FALSE);
}
