/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   star.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:40:48 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:40:59 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "glob.h"
#include <sys/dir.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

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
