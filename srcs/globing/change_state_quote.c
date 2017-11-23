#include "glob.h"

static void		quotement(int *quoted, int what)
{
	if (*quoted == 0)
		*quoted = what;
	else if (*quoted == what)
		*quoted = 0;
}

int				change_state_quote(char c, int quoted)
{
	if (c == '\'' && quoted != 3)
		quotement(&quoted, 1);
	else if (c == '"' && quoted != 3)
		quotement(&quoted, 2);
	else if (c == '\\')
		quotement(&quoted, 3);
	else
	{
		if (quoted == 3)
			quoted = 0;
	}
	return (quoted);
}
