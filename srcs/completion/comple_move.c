/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comple_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:47 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:07 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"
#include "line_editing.h"

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
