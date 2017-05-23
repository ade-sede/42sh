#include "completion.h"
#include "line_editing.h"

char	**array_dir_matches(char *to_match)
{
	struct dirent	*dirent;
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
	(void)to_match;
	return (matches);
}

int	comple_init_winch(t_comple *c)
{
	unsigned int	n;

	n = c->nb_matches;
	c->ws_col = get_ws_col();
	c->ws_col = get_ws_col() / (c->max_len + 1);
	c->nb_lines = (n % c->ws_col == 0) ? n / c->ws_col : (n / c->ws_col) + 1;
	return (1);
}

int	comple_init(t_line *line, t_comple *c)
{
	char		*to_match;

	to_match = NULL;
	c->matches = array_dir_matches(to_match);
	c->max_len = ft_arraymax_f((const char**)c->matches, ft_strlen);
	c->nb_matches = ft_arraylen((const char**)c->matches);
	comple_init_winch(c);
	c->pos = -1;
	if (c->nb_matches == 1)
	{
		c->pos = 0;
		comple_exit_matched(line, *c);
		return (0);
	}
	return (1);
}
