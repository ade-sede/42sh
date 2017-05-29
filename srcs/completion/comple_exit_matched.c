#include "completion.h"
#include "line_editing.h"

void	comple_clear(t_comple c)
{
	//put_termcap("do");	
	//put_termcap("cr");	
	ft_putchar('\n');
	//goto_termcap("DL", 0, c.nb_lines);
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
	(void)line;
	//printf("\nto_replace %s, match %s\n", c.to_replace, c.matches[c.pos]);
	delete_word(c.to_replace);
	//printf("\nto_replace %s, match %s\n", c.to_replace, c.matches[c.pos]);
	edit_insert_str(line, c.to_replace, c.matches[c.pos]);
	//ft_strncpy(c.to_replace, c.matches[c.pos], ft_strlen(c.matches[c.pos]));
	comple_clear(c);
	put_termcap("up");
	comple_free(c);
	return (1);
}
