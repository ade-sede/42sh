#include "glob.h"
#include <sys/dir.h>
#include <sys/types.h>
#include <dirent.h>

char	*init_regex(char *regex, int *r_i)
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
			*r_i = 1;
			return (ft_strdup("/"));
		}
		*r_i = last_slash;
		return (ft_strndup(regex, last_slash - 1));
	}
	*r_i = 0;
	return (ft_strdup("."));
}

int		func_cmp(t_matches *m, int m_i, int r_i)
{
	int backslash;

	backslash =(m->regex[r_i] == '\\' && m->regex[r_i + 1] == '\\');
	if (m->regex[r_i] != '\\' || backslash)
	{
		if (m->regex[r_i] == m->to_match[m_i])
			return (match(m, m_i + 1, r_i + 1 + backslash));
		return (0);
	}
	else
		return (match(m, m_i, r_i + 1));
}

int		has_glob_char(char *expr)
{
	size_t	i;
	int		quoted;

	quoted = 0;
	i = 0;
	while (expr[i])
	{
		if (quoted == 0 && ft_strchr("*[?", expr[i]))
			return (1);
		quoted = change_state_quote(expr[i], quoted);
//		fprintf(stderr, "end_bracket quoted: %d, %c\n", quoted, expr[i]);
		i++;
	}
	return (0);
}

t_list	*glob(char *regex)
{
	t_matches	m;
	char		*dir_name;
	int			r_i;
	int			m_i;

	dir_name = init_regex(regex, &r_i);
	if (r_i - 1 >= 0)
		m_i = r_i - 1;

	else
		m_i = 0;

#ifdef GLOB_DEBUG
 printf("regex: %s\n", regex);
 #endif
	m =(t_matches){NULL, NULL, regex, dir_name};
	if (!match_open_dir(&m, m_i, r_i, dir_name))
		return (NULL);
	return (m.list);
}
