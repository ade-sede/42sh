/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:41:03 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/16 02:27:01 by vcombey          ###   ########.fr       */
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

	i = to_match_i;
	bool_match = 0;
	while (!bool_match && m->to_match[i])
	{
		bool_match || (bool_match |= match(m, i, regex_i + 1));
		i++;
	}
	bool_match || (bool_match |= match(m, i, regex_i + 1));
	return (bool_match);
}
