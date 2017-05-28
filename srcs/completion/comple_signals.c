#include "completion.h"
#include "line_editing.h"

void	comple_handle_sigwinch(int signum)
{
	//put_termcap("cr");
	//put_termcap("cd");
	//comple_clear(*singleton_comple());
	comple_init_winch(singleton_comple());
	comple_clear(*singleton_comple());
	put_termcap("cl");
	comple_refresh(singleton_line(), *singleton_comple());
	(void)signum;
}

void	comple_handle_sigint(int signum)
{
	move_cursor_lastline(singleton_line());
	edit_line_init();
	comple_clear(*singleton_comple());
	put_prompt(NULL);
	(void)signum;
}

void	comple_set_signals(void)
{
	signal(SIGWINCH, comple_handle_sigwinch);
	signal(SIGINT, comple_handle_sigint);
}
