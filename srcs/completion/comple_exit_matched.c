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

int	comple_exit_matched(t_line *line, t_comple c)
{
	size_t	selected_len;
	char	*selected_str;
	
	selected_str = c.matches[c.pos];
	selected_len = ft_strlen(selected_str);
	if (line->pos == line->len - 1)
		ft_strcpy(line->buff + line->len, selected_str);
	else
	{
		ft_memmove((void*)(line->buff + line->pos + selected_len), (void*)(line->buff + line->pos), line->len - line->pos);
		ft_strcpy(line->buff + line->pos, selected_str);
	}
	line->pos += selected_len;
	line->len += selected_len;
	comple_clear(c);
	put_termcap("up");	
	comple_free(c);
	return (1);
}
