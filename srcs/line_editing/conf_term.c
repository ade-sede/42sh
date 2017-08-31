#include "line_editing.h"
#include <stdio.h>

void	conf_term_canonical(void)
{
	if (tcsetattr(0, TCSADRAIN, &singleton_line()->canonical_mode))
		fatal("tcsetattr error");
}

void	conf_term_normal(void)
{
	if (tcsetattr(0, TCSADRAIN, &singleton_line()->normal_mode))
		fatal("tcsetattr error");
}

void	conf_term_in(void)
{
	char			*termtype;
	struct termios	term;
	t_line			*line;

	line = singleton_line();
	if ((termtype = getenv("TERM")) == NULL)
		termtype = "xterm";
	if (tgetent(NULL, termtype) <= 0)
		fatal("cant access data base");
	if (tcgetattr(0, &term) == -1)
		fatal("getattr error");
	ft_memcpy(&line->normal_mode, &term, sizeof(struct termios));
	ft_memcpy(&line->canonical_mode, &line->normal_mode,
			sizeof(struct termios));
	line->canonical_mode.c_lflag &= ~(ICANON);
	line->canonical_mode.c_lflag &= ~(ECHO);
	line->canonical_mode.c_cc[VMIN] = 1;
	line->canonical_mode.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &line->canonical_mode) < 0)
		fatal("tcsetattr error");
}
