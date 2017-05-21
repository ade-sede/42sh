#include "completion.h"
#include "line_editing.h"

char	**array_dir_matches(char *to_match)
{

	struct dirent	*dirent;
	t_item			*new;
	t_item			*error;
	DIR				*dir;
	char		**matches;
	int		i;

	i = 0;
	matches = ft_memalloc(sizeof(char *) * 100); 
	dir = opendir(".");
	while ((dirent = readdir(dir)) != NULL)
	{
		matches[i] = ft_strdup(dirent->d_name);
		i++;
	}
	closedir(dir);
	return (matches);
}

int	comple_init(t_line line, t_comple *c)
{
	char		*to_match;
	unsigned int	n;

	c->matches = array_dir_matches(to_match);
	c->max_len = ft_arraymax_f(c->matches, ft_strlen);
	c->nb_matches = ft_array_len(c->matches);
	n = c->nb_matches;
	c->ws_col = get_ws_col();
	if ((c->nb_col = get_ws_col() / (c->max_name + 1)) == 0)
		return (0);
	c->nb_lines = (n % c->nb_col == 0) ? n / c->nb_col : (n / c->nb_col) + 1;
	c->pos = 0;
	if (c->nb_matches == 1)
	{
		comple_exit_matched();
		return (0);
	}
	return (1);
}
