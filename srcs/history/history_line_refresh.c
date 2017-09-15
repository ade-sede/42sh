/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_line_refresh.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/15 22:41:02 by vcombey           #+#    #+#             */
/*   Updated: 2017/09/15 22:41:13 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history.h"
#include "line_editing.h"

void	history_line_refresh(t_line *line, char *new_line)
{
	ft_strclr(line->buff);
	edit_insert_str(line, line->buff, new_line);
	line->len = ft_strlen((const char *)new_line);
	line->pos = line->len;
	edit_refresh(line);
}
