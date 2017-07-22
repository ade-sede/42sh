/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_insert_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 23:19:54 by vcombey           #+#    #+#             */
/*   Updated: 2017/07/22 18:57:54 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include "libft.h"

int	ft_insert_str_dest(char *dest, char *str)
{
	size_t	len;
	len = ft_strlen(str);
	ft_memmove((void*)(dest + len), (void*)(dest), ft_strlen(dest));
	ft_strncpy(dest, str, len);
	return (1);
}

int	edit_insert_str(t_line *line, char *dest, char *str)
{
	size_t	len;

	len = ft_strlen(str);
	if (line->len + len >= line->size)
	    realoc_line_buff(&line->buff, &line->size, line->len + len);
	ft_insert_str_dest(dest, str);
	line->pos = dest - line->buff + len;
	line->len = ft_strlen(line->buff);
	return (1);
}
