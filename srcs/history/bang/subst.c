/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subst.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:36 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:17 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bang.h"
#include "libft.h"

static int	else_routine(struct s_parse_mod *p, t_word new, size_t *i)
{
	if (charcmp(p->cache.str, *i, '&'))
	{
		if (new.str)
			w_addstr(&p->tmp, new.str);
	}
	else if (!charcmp(p->cache.str, *i, '\\'))
		w_addchar(&p->tmp, p->cache.str[*i]);
	++(*i);
	return (FALSE);
}

static int	perform_substitute(struct s_parse_mod *p, t_word old, t_word new)
{
	size_t	i;
	size_t	len;
	int		done;

	if (!old.str)
		return (TRUE);
	i = 0;
	done = TRUE;
	len = ft_strlen(old.str);
	while (p->cache.str[i])
	{
		if (ft_strnequ(p->cache.str + i, old.str, len) && (done || p->g_flag))
		{
			done = FALSE;
			if (new.str)
				w_addstr(&p->tmp, new.str);
			i += len;
		}
		else
			else_routine(p, new, &i);
	}
	return (FALSE);
}

static int	parse_sub(const char **source, \
		t_word *old, t_word *new, const char *s)
{
	char	delim;

	delim = **source;
	if (!**source)
		return (TRUE);
	++(*source);
	while (**source && !charcmp(s, *source - s, delim))
	{
		w_addchar(old, **source);
		++(*source);
	}
	if (!old->str)
		return (TRUE);
	if (**source == delim)
		++(*source);
	while (**source && !charcmp(s, *source - s, delim) && **source != '\n')
	{
		w_addchar(new, **source);
		++(*source);
	}
	if (**source == delim)
		++(*source);
	return (FALSE);
}

int			substitute(const char **source, struct s_parse_mod *p)
{
	t_word		new;
	t_word		old;
	const char	*s;

	w_newword(&new);
	w_newword(&old);
	s = *source;
	if (**source == 'g')
	{
		p->g_flag = 1;
		++(*source);
		if (**source != 's')
			return (TRUE);
	}
	++(*source);
	if (parse_sub(source, &old, &new, s))
		return (TRUE);
	if (perform_substitute(p, old, new))
		return (TRUE);
	w_free(&new);
	w_free(&old);
	return (FALSE);
}
