/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trunc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:36 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:17 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "bang.h"

static int	h_routine(struct s_parse_mod *p)
{
	ssize_t	h_i;
	ssize_t	h_end;

	h_i = 0;
	h_end = ft_strrichr(p->cache.str, '/');
	while (p->cache.str[h_i] && h_i != h_end)
	{
		w_addchar(&p->tmp, p->cache.str[h_i]);
		++h_i;
	}
	return (42);
}

static int	t_routine(struct s_parse_mod *p)
{
	ssize_t	t_i;

	t_i = ft_strrichr(p->cache.str, '/');
	++t_i;
	while (p->cache.str[t_i])
	{
		w_addchar(&p->tmp, p->cache.str[t_i]);
		++t_i;
	}
	return (42);
}

static int	r_routine(struct s_parse_mod *p)
{
	ssize_t	r_i;
	ssize_t	r_end;

	r_i = 0;
	r_end = ft_strrichr(p->cache.str, '.');
	while (p->cache.str[r_i] && r_i != r_end)
	{
		w_addchar(&p->tmp, p->cache.str[r_i]);
		++r_i;
	}
	return (42);
}

static int	e_routine(struct s_parse_mod *p)
{
	ssize_t	e_i;

	e_i = ft_strrichr(p->cache.str, '.');
	++e_i;
	while (p->cache.str[e_i])
	{
		w_addchar(&p->tmp, p->cache.str[e_i]);
		++e_i;
	}
	return (42);
}

void		trunc_routines(const char **source, struct s_parse_mod *p)
{
	if (**source == 'h')
		h_routine(p);
	else if (**source == 't')
		t_routine(p);
	else if (**source == 'r')
		r_routine(p);
	else if (**source == 'e')
		e_routine(p);
	++(*source);
}
