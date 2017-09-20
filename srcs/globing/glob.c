#include "glob.h"
#include <sys/dir.h>
#include <sys/types.h>
#include <dirent.h>

char	*init_regex(char *regex, size_t *regex_i)
{
	size_t	last_slash;
	size_t	i;

	last_slash = 0;
	i = 0;
	while (regex[i] && !(ft_is_one_of(regex[i], "[]*")))
	{
		if (regex[i] == '/')
			last_slash = i + 1;
		i++;
	}
	if (last_slash != 0)
	{
		if (last_slash == 1 && regex[0] == '/')
		{
			*regex_i = 1;
			return (ft_strdup("/"));
		}
		*regex_i = last_slash;
		return (ft_strndup(regex, last_slash - 1));
	}
	*regex_i = 0;
	return (ft_strdup("."));
}

int		func_cmp(t_matches *m, int to_match_i, int regex_i)
{
	if (m->regex[regex_i] == m->to_match[to_match_i])
		return (match(m, m->regex[regex_i] == '\\' ? \
					to_match_i + 2 : to_match_i + 1, regex_i + 1));
	else
		return (0);
}

t_list	*glob(char *regex)
{
	t_matches	m;
	char		*dir_name;
	size_t		regex_i;
	size_t		to_match_i;

	dir_name = init_regex(regex, &regex_i);
	to_match_i = regex_i - 1;
	m = (t_matches){NULL, NULL, regex, dir_name};
	if (!match_open_dir(&m, to_match_i, regex_i, dir_name))
		return (ft_simple_lst_create(ft_strdup(m.regex)));
	return (m.list);
}
