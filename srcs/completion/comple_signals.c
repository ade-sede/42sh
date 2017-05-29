#include "completion.h"
#include "line_editing.h"

void	comple_handle_sigwinch(t_line *line, t_comple *c)
{
	//put_termcap("cr");
	//put_termcap("cd");
	//comple_clear(*c());
	comple_init_winch(c);
	comple_clear(*c);
	put_termcap("cl");
	comple_refresh(line, *c);
}

void	comple_handle_sigint(t_line *line, t_comple *c)
{
	move_cursor_lastline(line);
	edit_line_init(line);
	comple_clear(*c);
	put_prompt(NULL);
}

void	comple_set_comple_signum(signum)
{
	singleton_comple()->signum = signum;
}

void	comple_set_signals(void)
{
	signal(SIGWINCH, comple_set_comple_signum);
	signal(SIGINT, comple_set_comple_signum);
}
