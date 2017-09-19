/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btsearch_refresh.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:48 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:17 by ade-sede         ###   ########.fr       */
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
