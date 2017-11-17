#include "t_history_h"

t_history	*singleton_history(void)
{
	static t_history hist;

	return (&hist);
}
