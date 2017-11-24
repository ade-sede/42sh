/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 19:08:36 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 19:18:56 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bang.h"
#include "libft.h"

void	init_p(struct s_parse_mod *p, t_word word_designator)
{
	w_newword(&p->cache);
	w_newword(&p->tmp);
	if (word_designator.str)
		w_addstr(&p->cache, word_designator.str);
	p->quote_mode = 0;
	p->g_flag = 0;
}

void	pop(t_word *old, t_word *new)
{
	w_free(old);
	w_newword(old);
	if (new->str)
		w_addstr(old, new->str);
	w_free(new);
	w_newword(new);
}
