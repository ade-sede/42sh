/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comple_glob_matches.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 10:59:08 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 12:52:55 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "completion.h"
#include "glob.h"

char	**comple_globing_matches(t_line *line, t_comple *c)
{
	char	**matches;
	t_list	*glob_list;
	t_list	*first;
	size_t	i;

	i = 0;
	c->to_replace = get_start_word_cursor(line);
	glob_list = glob(c->current_word);
	first = glob_list;
	matches = ft_memalloc(sizeof(char*) * 2);
	matches[0] = ft_strdup(glob_list->data);
	glob_list = glob_list->next;
	while (glob_list)
	{
		matches[0] = ft_strchange(matches[0], \
				ft_strsurround(matches[0], " ", glob_list->data));
		glob_list = glob_list->next;
	}
	ft_simple_lst_remove(&first, ft_free);
	return (matches);
}
