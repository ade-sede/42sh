/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   apply_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 19:10:16 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 19:13:53 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bang.h"
#include "libft.h"

static int	routine(struct s_parse_mod *p, int *escape, size_t *i)
{
	*escape = FALSE;
	if (p->quote_mode == 'x' && ft_strchr("\t \n", p->cache.str[*i]))
	{
		w_addchar(&p->tmp, '\'');
		*escape = TRUE;
	}
	else if (p->cache.str[*i] == '\'')
	{
		w_addchar(&p->tmp, '\'');
		w_addchar(&p->tmp, '\\');
		*escape = TRUE;
	}
	w_addchar(&p->tmp, p->cache.str[*i]);
	if (*escape)
		w_addchar(&p->tmp, '\'');
	++(*i);
	return (1);
}

int			apply_quotes(struct s_parse_mod *p)
{
	size_t	i;
	int		escape;

	i = 0;
	escape = FALSE;
	if (!p->cache.str)
		return (TRUE);
	w_addchar(&p->tmp, '\'');
	while (p->cache.str[i])
		routine(p, &escape, &i);
	w_addchar(&p->tmp, '\'');
	pop(&p->cache, &p->tmp);
	return (FALSE);
}
