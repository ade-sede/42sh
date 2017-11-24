/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_insert_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 23:13:37 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 23:14:33 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		realoc_line_buff(line, line->len + len + 1);
	ft_insert_str_dest(line->buff + dest_pos, str, dest_len);
	line->pos = dest_pos + len;
	line->len = ft_strlen(line->buff);
	return (1);
}
