/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:36 by ade-sede          #+#    #+#             */
/*   Updated: 2018/05/25 20:42:44 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/dir.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include "glob.h"

int		func_star(t_matches *m, int m_i, int r_i)
{
	int		bool_match;
	int		i;

	i = m_i;
	bool_match = 0;
	if (m->to_match[i] == '.')
		return (0);
	while (!bool_match && m->to_match[i])
	{
		if (!bool_match)
			(bool_match |= match(m, i, r_i + 1));
		i++;
	}
	if (!bool_match)
		(bool_match |= match(m, i, r_i + 1));
	return (bool_match);
}
