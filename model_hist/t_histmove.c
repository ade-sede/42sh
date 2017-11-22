#include "t_history.h"
#include "failure.h"
#include "environ.h"
#include "libft.h"
#include <sys/time.h>
#include "get_next_line.h"

int         history_up(t_history *hist)
{
	if (hist->current_node->prev)
		hist->current_node = hist->current_node->prev;
	return (1);
}
