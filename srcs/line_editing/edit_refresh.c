#include "line_editing.h"

void	edit_refresh(int signum, t_env *env)
{
	int	n;

	//ft_putchar('\n');
	//put_termcap("up");
	put_termcap("cr");
	put_termcap("dl");
	put_prompt(env);
	ft_putstr(line()->buff);
	n = line()->len - line()->pos;
	put_ntermcap("le", n);
	(void)signum;
}

