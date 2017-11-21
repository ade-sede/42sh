#include "t_history.h"
#include "failure.h"
#include "environ.h"
#include "libft.h"
#include <sys/time.h>
#include "get_next_line.h"

t_history		*singleton_history(void)
{
	static t_history hist;

	return (&hist);
}

void	history_init_line(t_history *hist)
{
	hist->current_node = hist->command_list->last;
}

void 		   push_in_hist_list_null(t_history *hist)
{
	t_list_d	*new;

	new = ft_double_lst_create(new_node());
	if (hist->command_list == NULL)
		hist->command_list = ft_create_head(new);
	else
		ft_double_lst_add(&hist->command_list, (new));
	hist->current_node = NULL;
}

void			init_history(t_history *hist)
{
	hist->command_list = NULL;
	hist->first_new_elem = NULL;
	hist->current_node = NULL;
	hist->history_line = 0;
	push_in_hist_list_null(hist);
}

char        *histfile(void)
{
	t_env   *env;
	char    *hist_file;

//	env = singleton_env();
//	hist_file = env_getenv((const char **)env->environ, "HISTFILE", NULL);
//	if (!hist_file)
		hist_file = HISTFILE;
	return (hist_file);
}
