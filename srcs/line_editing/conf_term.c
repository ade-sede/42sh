#include "line_editing.h"

void	conf_term_out(void)
{
	if (tcsetattr(0, TCSADRAIN, line()->old_term))
		fatal("tcsetattr error");
}

void	conf_term_in(void)
{
	char			*termtype;
	char			term_buffer[4096];
	struct termios	term;

	if ((termtype = getenv("TERM")) == NULL)
		termtype = "xterm";
	if (tgetent(term_buffer, termtype) <= 0)
		fatal("cant access data base");
	if (tcgetattr(0, &term) == -1)
		fatal("getattr error");
	line()->old_term = &term;
	term.c_lflag &= ~(ICANON);
	term.c_lflag &= ~(ECHO);
	term.c_cc[VMIN] = 1;
	term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSADRAIN, &term) < 0)
		fatal("tcsetattr error");
}
