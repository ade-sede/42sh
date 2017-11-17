#include "glob.h"
#include <sys/dir.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int	func_star(t_matches *m, int m_i, int r_i)
{
	int	bool_match;
	int	i;

	i = m_i;
	bool_match = 0;
//	printf("star mi: %c\n", m->to_match[i]);
	if (m->to_match[i] == '.')
		return (0);
	while (!bool_match && m->to_match[i])
	{
		bool_match || (bool_match |= match(m, i, r_i + 1));
		i++;
	}
	bool_match || (bool_match |= match(m, i, r_i + 1));
	return (bool_match);
}
