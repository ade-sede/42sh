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

char	**comple_globing_matches(t_line *line, t_comple *c, t_list *glob_list)
{
	char	**matches;
	t_list	*first;
	size_t	i;

	i = 0;
	c->to_replace = get_start_word_cursor(line);
	first = glob_list;
	matches = ft_memalloc(sizeof(char*) * 2);
	matches[0] = ft_strdup(((t_token *)glob_list->data)->value);
	glob_list = glob_list->next;
	while (glob_list)
	{
		matches[0] = ft_strchange(matches[0], \
				ft_strsurround(matches[0], " ",
					((t_token *)glob_list->data)->value));
		glob_list = glob_list->next;
	}
	ft_simple_lst_remove(&first, free_token);
	return (matches);
}
