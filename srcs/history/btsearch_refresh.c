#ifndef NO_TERMCAPS
#include "line_editing.h"
#include "history.h"
#include <stdio.h>

void	btsearch_refresh(t_line *line, t_hist *h)
{
	char	*search_line;

	edit_refresh_clear(line);
//	move_cursor_firstline_from_prev_pos(line);
	move_cursor_lastline_from_first_line(line);
	ft_putchar('\n');
	search_line = (h->btsearch_cur == NULL) ? "failing bck-i-search: " : \
				"bck-i-search: ";
	search_line = ft_strjoin_free(search_line, h->btsearch_buff, 0);
	edit_refresh_nchar(line, 0, search_line, ft_strlen(search_line));
	ft_putchar('_');
	put_ntermcap("up", ft_strlen(search_line) / line->ws_col + 1);
	move_cursor_firstline_from_lastline(line);
	put_prompt(line);
	edit_refresh_line(line);
	edit_refresh_cursor(line);
	free(search_line);
	(void)h;
}
#endif
