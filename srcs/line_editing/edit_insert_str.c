/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_insert_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:40:47 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:40:58 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include "libft.h"

int	ft_insert_str_dest(char *dest, char *str, size_t dest_len)
{
	size_t	len;

	len = ft_strlen(str);
	ft_memmove((void*)(dest + len), (void*)(dest), dest_len);
	ft_strncpy(dest, str, len);
	return (1);
}

int	edit_insert_str(t_line *line, char *dest, char *str)
{
	size_t	len;
	size_t	dest_pos;
	size_t	dest_len;

	dest_pos = dest - line->buff;
	dest_len = ft_strlen(dest);
	len = ft_strlen(str);
	if (line->len + len >= line->size)
		realoc_line_buff(&line->buff, &line->size, line->len + len);
	ft_insert_str_dest(line->buff + dest_pos, str, dest_len);
	line->pos = dest_pos + len;
	line->len = ft_strlen(line->buff);
	return (1);
}
