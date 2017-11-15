#include "glob.h"
#include <sys/dir.h>
#include <sys/types.h>
#include <dirent.h>

int		char_is_escaped(char *regex, int regex_i)
{
	size_t	nb_bslash;

	if (regex_i == 0)
		return (0);
	regex_i--;
	nb_bslash = 0;
	while (regex[regex_i] == '\\')
	{
		nb_bslash++;
		if (regex_i == 0)
			break ;
		regex_i--;
	}
	return (nb_bslash % 2);
}

int		stop_condition(t_matches *m)
{
	ft_simple_lst_add(&m->list, \
			ft_simple_lst_create(ft_strdup(m->to_match)));
	return (1);
}

int		match(t_matches *m, int to_match_i, int regex_i)
{
	if (m->to_match[to_match_i] == '\0' && m->regex[regex_i] == '\0') //attention
		return (stop_condition(m));
	else if (m->to_match[to_match_i] == '\0' && m->regex[regex_i] != '\0' \
			&& m->regex[regex_i] != '*' && m->regex[regex_i] != '/')
		return (0);
	if (m->regex[regex_i] == '/' && m->to_match[to_match_i] == '\0')
	{
		return (match_open_dir(m, to_match_i, regex_i + 1, \
					ft_strdup(m->to_match)));
	}
	if (m->regex[regex_i] == '*' && !char_is_escaped(m->regex, regex_i) && \
			!(m->regex[regex_i + 1] == '*'))
		return (func_star(m, to_match_i, regex_i));
	if (m->regex[regex_i] == '*' && !char_is_escaped(m->regex, regex_i) && \
			(m->regex[regex_i + 1] == '*'))
		return (match(m, to_match_i, regex_i + 1));
	if (m->regex[regex_i] == '?' && !char_is_escaped(m->regex, regex_i))
		return (match(m, to_match_i + 1, regex_i + 1));
	if (m->regex[regex_i] == '[' && valid_square_bracket(m->regex, regex_i))
		return (func_square_bracket(m, to_match_i, regex_i));
	if (m->regex[regex_i] != '\\' || (m->regex[regex_i] == '\\' && \
				m->regex[regex_i + 1] == '\\'))
		return (func_cmp(m, to_match_i, regex_i));
	return (match(m, to_match_i, regex_i + 1));
}
