#include "completion.h"
#include "line_editing.h"

void	comple_clear(t_comple c)
{
	//put_termcap("do");	
	//put_termcap("cr");	
	ft_putchar('\n');
	put_termcap("cd");	
	(void)c;
	//put_ntermcap("dl", c.nb_lines);	
}

void	comple_free(t_comple c)
{
	ft_arraydel(&c.matches);
}

int	insert_str_linebuff(char *str, char *dest)
{
	size_t	len;

	len = ft_strlen(str);
	ft_memmove((void*)(dest + len), (void*)(dest), ft_strlen(dest));
	//memset(dest, 48, ft_strlen(dest));
	//ft_putendl(dest);
	ft_strncpy(dest, str, len);
	return (1);
}

int	comple_exit_matched(t_line *line, t_comple c)
{
	size_t	selected_len;
	char	*selected_str;
	
	selected_str = c.matches[c.pos];
	selected_len = ft_strlen(selected_str);
	if (line->pos == line->len)
		ft_strcpy(line->buff + line->len, selected_str);
	else
		insert_str_linebuff(selected_str, line->buff + line->pos);
	line->pos += selected_len;
	line->len += selected_len;
	comple_clear(c);
	put_termcap("up");	
	comple_free(c);
	return (1);
}
