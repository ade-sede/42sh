/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comple_glob_matches.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:34 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:13:51 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "completion.h"
#include "glob.h"
#include <stdio.h>

char	**comple_globing_matches(t_line *line, t_comple *c, char **glob_list)
{
	char	**matches;

	c->to_replace = get_start_word_cursor(line);
	matches = ft_memalloc(sizeof(char*) * 2);
	matches[0] = ft_strdup(*glob_list);
	while (*++glob_list)
	{
		matches[0] = ft_strchange(matches[0], \
				ft_strsurround(matches[0], " ", *glob_list));
	}
	return (matches);
}
