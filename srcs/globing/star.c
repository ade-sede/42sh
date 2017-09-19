/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:47 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:15 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include <sys/dir.h>
#include <sys/types.h>
#include <dirent.h>

int	func_star(t_matches *m, int to_match_i, int regex_i)
{
	int	bool_match;
	int	i;
	char	*to_match_cpy;

	i = to_match_i;
	bool_match = 0;
	to_match_cpy = ft_strdup(m->to_match);
	while (!bool_match && m->to_match[i])
	{
		bool_match || (bool_match |= match(m, i, regex_i + 1));
		i++;
	}
	bool_match || (bool_match |= match(m, i, regex_i + 1));
	return (bool_match);
}
