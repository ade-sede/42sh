/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comple_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:53 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include "completion.h"

int		comple_right(t_comple *c)
{
	if (c->nb_matches - (size_t)c->pos < c->nb_matches % c->nb_lines + 1)
		c->pos -= c->nb_lines - c->nb_matches % c->nb_lines;
	else if (c->nb_matches - (size_t)c->pos <= c->nb_lines)
		c->pos += c->nb_matches % c->nb_lines;
	c->pos += c->nb_lines;
	c->pos += c->nb_matches;
	c->pos %= c->nb_matches;
	return (1);
}

int		comple_left(t_comple *c)
{
	if ((size_t)c->pos < c->nb_matches % c->nb_lines)
		c->pos += c->nb_lines - c->nb_matches % c->nb_lines;
	else if ((size_t)c->pos < c->nb_lines)
		c->pos -= c->nb_matches % c->nb_lines;
	c->pos -= c->nb_lines;
	c->pos += c->nb_matches;
	c->pos %= c->nb_matches;
	return (1);
}

int		comple_up(t_comple *c)
{
	c->pos -= 1;
	c->pos += c->nb_matches;
	c->pos %= c->nb_matches;
	return (1);
}

int		comple_down(t_comple *c)
{
	c->pos += 1;
	c->pos += c->nb_matches;
	c->pos %= c->nb_matches;
	return (1);
}
