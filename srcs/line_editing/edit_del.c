#include "line_editing.h"
#include "failure.h"

/*
**	Function used to delete a character in buff, when backspace is pressed by
**	the user.
**	All the buffer from line->pos to line->len is shifted one time to the left.
**	
**	Side note : Calling the refresh routines manually because if the character
**	removed is a newline, the line cannot be cleared correctly anymore.
*/
int	edit_backspace(t_line *line)
{
	if (line->pos == 0)
		return (0);
	edit_refresh_clear(line);
	ft_memmove((void*)(line->buff + line->pos - 1), \
			(void*)(line->buff + line->pos), line->len - line->pos);
	line->buff[line->len - 1] = '\0';
	line->pos--;
	line->len--;
	put_prompt(line);
	edit_refresh_line(line);
	edit_refresh_cursor(line);
	return (1);
}
