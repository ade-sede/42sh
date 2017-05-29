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

	ft_insert_str_dest(dest, str);
	len = ft_strlen(str);
	line->pos = dest - line->buff + len;
	line->len = ft_strlen(line->buff);
	return (1);
}
