#include "line_editing.h"

int	ft_insert_str_dest(char *str, char *dest)
{
	size_t	len;

	len = ft_strlen(str);
	ft_memmove((void*)(dest + len), (void*)(dest), ft_strlen(dest));
	ft_strncpy(dest, str, len);
	return (1);
}

int	edit_insert_str(t_line *line, char *str)
{
	size_t	len;

	ft_insert_str_dest(str, line->buff + line->pos);
	len = ft_strlen(str);
	line->pos += len;
	line->len += len;
	return (1);
}
