#ifndef LINE_EDITING_H
# define LINE_EDITING_H

# include "env.h"
# include "termios.h"
# include "term.h"

typedef struct		s_line
{
	unsigned int		pos;
	unsigned int		len;
	char		*buff;
	struct termios	*old_term;
}			t_line;

char	*edit_get_input(t_env *env);
void	conf_term_in(void);
void	conf_term_out(void);
void	put_termcap(char *capacity)

int		edit_end(t_line *line)
int		edit_home(t_line *line)
int		edit_right(t_line *line)
int		edit_left(t_line *line)
void	edit_del(t_line *line)
void	edit_add(int keycode, t_line *line)

# endif
