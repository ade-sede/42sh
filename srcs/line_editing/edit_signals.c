#include "completion.h"
#include "line_editing.h"

void	edit_handle_sigwinch(int signum)
{
	//put_termcap("cr");
	//put_termcap("cd");
	//comple_clear(*singleton_comple());
	singleton_comple()->ws_col = get_ws_col();
	singleton_line()->ws_col = get_ws_col();
	//edit_clear(*singleton_comple());
	//put_termcap("cl");
	edit_refresh(singleton_line());
	(void)signum;
}

void	edit_handle_sigstop(int signum)
{
	move_cursor_lastline(singleton_line());
	edit_line_init();
	ft_putchar('\n');	
	put_prompt(NULL);
	(void)signum;
}

void	edit_set_signals(void)
{
	signal(SIGINT, edit_handle_sigstop);
	signal(SIGWINCH, edit_handle_sigwinch);
}
