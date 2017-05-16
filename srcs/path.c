/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 17:57:52 by ade-sede          #+#    #+#             */
/*   Updated: 2017/05/16 12:10:16 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"
#include <stdio.h>

void	create_path_list(char *path, t_list **first)
{
	t_list	*node;
	ssize_t	colon_index;

	colon_index = 0;
	while (*path)
	{
		colon_index = ft_strichr(path, ':');
		if (colon_index > 0)
			node = ft_simple_lst_create(ft_strsub((const char*)path, 0, colon_index));
		else
			node = ft_simple_lst_create(ft_strdup((const char*)path));
		if (*first == NULL)
			*first = node;
		else if (colon_index > 0)
			ft_simple_lst_pushback(first, node);
		path += (colon_index == -1) ? (int)ft_strlen((const char*)path) : (int)(colon_index + 1);
	}
}
