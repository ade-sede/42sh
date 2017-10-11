/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btsearch_refresh.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/11 22:40:48 by vcombey           #+#    #+#             */
/*   Updated: 2017/10/11 22:40:59 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "line_editing.h"
#include "history.h"

void	btsearch_refresh(t_line *line, t_hist *h)
{
	char	*search_line;

	edit_refresh_clear(line);
	move_cursor_lastline_from_first_line(line);
	ft_putchar_fd('\n', 2);
	search_line = (h->btsearch_cur == NULL) ? "failing bck-i-search: " : \
				"bck-i-search: ";
	search_line = ft_strjoin_free(search_line, h->btsearch_buff, 0);
	ft_putstr_fd(search_line, 2);
	ft_putchar_fd('_', 2);
	put_ntermcap("up", ft_strlen(search_line) / line->ws_col + 1);
	move_cursor_firstline_from_lastline(line);
	put_prompt(line);
	edit_refresh_line(line);
	edit_refresh_cursor(line);
	free(search_line);
	(void)h;
}
