#include "completion.h"
#include "history.h"
#include "line_editing.h"

int	abort_opening;

void	edit_handle_sigwinch(int signum)
{
	singleton_comple()->ws_col = get_ws_col();
	singleton_line()->ws_col = get_ws_col();
	(void)signum;
}

void	edit_handle_sigint_open(int signum)
{
	history_init(singleton_hist());
	move_cursor_lastline(singleton_line());
	edit_line_init(singleton_line(), &edit_set_signals_open);
	ft_putchar_fd('\n', 2);
	put_prompt(singleton_line());
	(void)signum;
}

void	edit_set_signals_open(void)
{
	signal(SIGINT, edit_handle_sigint_open);
	signal(SIGWINCH, edit_handle_sigwinch);
}

void	edit_set_signals_reopen(void)
{
	signal(SIGINT, edit_handle_sigint_reopen);
	signal(SIGWINCH, edit_handle_sigwinch);
}

void	edit_handle_sigint_reopen(int signum)
{
	move_cursor_lastline(singleton_line());
	ft_putchar_fd('\n', 2);
	abort_opening = 1;
	(void)signum;
}
