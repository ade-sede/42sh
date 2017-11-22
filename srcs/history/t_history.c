#include "t_history.h"
#include "libft.h"
#include "environ.h"

t_history		*singleton_history(void)
{
	static t_history hist;

	return (&hist);
}

/*
** This function should occur in main, only if the shell is interactive. It loads the history for the very first time.
** It loads the history file structure, and reads the history file.
*/
void		init_history(t_env *env, t_history *hist)
{
	const char *filename;
	t_histfile	*histfile;

	hist->command_list = NULL;
	hist->current_node = NULL;
	hist->new_command = NULL;
	hist->histfile_list = NULL;
	filename = env_getenv((const char **)env->environ, "HISTFILE", NULL);
	histfile = add_histfile(&hist->histfile_list, filename);
	history_read_file(hist, histfile->filename, &histfile->ln, &histfile->last_cmd);
}
