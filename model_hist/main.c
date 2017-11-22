#include "t_history.h"
#include "libft.h"

int main()
{
	t_history *hist;
	
	hist = singleton_history();
	init_history(hist);
	
	history_load(hist);

	builtin_history(NULL, NULL);
}
