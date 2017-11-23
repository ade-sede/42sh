#include "glob.h"

int		change_state_quote(char c, int quoted)
{
	if (c == '\'' && quoted != 3)
	{
		if (quoted == 0)
			quoted = 1;
		else if (quoted == 1)
			quoted = 0;
	}
	else if (c == '"' && quoted != 3)
	{
		if (quoted == 0)
			quoted = 2;
		else if (quoted == 2)
			quoted = 0;
	}
	else if (c == '\\')
	{
		if (quoted == 0)
			quoted = 3;
		else if (quoted == 3)
			quoted = 0;
	}
	else if (quoted == 3)
		quoted = 0;
	return (quoted);
}
