#include "line_editing.h"

t_line		*line(void)
{
	static t_line	s;

	return (&s);
}

void	edit_add(int keycode, t_line *line)
{
	if (line->pos == line->len - 1)
		line->buff[line->len] = (char)keycode;
	else
	{
		ft_memmove((void*)(line->buff + line->pos + 1), (void*)(line->buff + line->pos), line->len - line->pos);
		line->buff[line->pos] = (char)keycode;
	}
	line->pos++;
	line->len++;
}

void	edit_refresh(int signum, t_env *env)
{
	int	i;
	int	n;

	put_termcap("cr");
	put_termcap("dl");
	put_prompt(env);
	ft_putstr(line()->buff);
	i = -1;
	n = line()->len - line()->pos;
	while (++i < n)
		put_termcap("le");
	(void)signum;
}

