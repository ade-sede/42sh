#include "line_editing.h"
#include "t_env.h"
#include "environ.h"

/*
**	Functions used to temper with the terminal's configuration.
*/

/*
**	The two following routines toggle the canonical mode ON and OFF.
*/

void	conf_term_non_canonical(void)
{
//	write(1, "deb", 1);
//	sleep(5);
//	write(1, "deb", 1);
	if (tcsetattr(0, TCSANOW, &singleton_line()->non_canonical_mode) < 0)
		fatal("tcsetattr error");
//	sleep(5);
//	write(1, "fin", 1);
}

void	conf_term_canonical(void)
{
	if (tcsetattr(0, TCSANOW, &singleton_line()->canonical_mode) < 0)
		fatal("tcsetattr error");
}

/*
**	Retrieves the terminal's current configuration, saves it in order to be
**	able to restore it, and toggles canonical mode.
*/

void	conf_term_in(void)
{
	char			*termtype;
	struct termios	term;
	t_line			*line;

	line = singleton_line();
	if ((termtype = env_getenv((const char**)singleton_env()->environ, \
					"TERM", NULL)) == NULL)
		termtype = "xterm";
	if (tgetent(NULL, termtype) <= 0)
		fatal("cant access data base");
	if (tcgetattr(0, &term) == -1)
		fatal("getattr error");
	ft_memcpy(&line->canonical_mode, &term, sizeof(struct termios));
	ft_memcpy(&line->non_canonical_mode, &line->canonical_mode,
			sizeof(struct termios));
	line->non_canonical_mode.c_lflag &= ~(ICANON);
	line->non_canonical_mode.c_lflag &= ~(ECHO);
	line->non_canonical_mode.c_cc[VMIN] = 1;
	line->non_canonical_mode.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &line->non_canonical_mode) < 0)
		fatal("tcsetattr error");
}
