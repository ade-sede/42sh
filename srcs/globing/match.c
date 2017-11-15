#include "glob.h"
#include <sys/dir.h>
#include <sys/types.h>
#include <dirent.h>

int		char_is_escaped(char *regex, int r_i)
{
	size_t	nb_bslash;

	if (r_i == 0)
		return (0);
	r_i--;
	nb_bslash = 0;
	while (regex[r_i] == '\\')
	{
		nb_bslash++;
		if (r_i == 0)
			break ;
		r_i--;
	}
	return (nb_bslash % 2);
}

int		stop_condition(t_matches *m)
{
	ft_simple_lst_pushback(&m->list, \
			ft_simple_lst_create(ft_strdup(m->to_match)));
	return (1);
}

int		match(t_matches *m, int m_i, int r_i)
{
//	printf("r_i: %c, m_i: %c\n", m->regex[r_i], m->to_match[m_i]);
	if (m->regex[r_i] == '\0' && m->to_match[m_i] == '\0') //attention
		return (stop_condition(m));
	else if (m->regex[r_i] != '\0' && m->to_match[m_i] == '\0' \
			&& m->regex[r_i] != '*' && m->regex[r_i] != '/')
		return (0);
	else if (m->regex[r_i] == '\0' && m->to_match[m_i] != '\0')
		return (0);
	if (m->regex[r_i] == '/' && m->to_match[m_i] == '\0')
		return (match_open_dir(m, m_i, r_i + 1, ft_strdup(m->to_match)));
	if (m->regex[r_i] == '*' && !char_is_escaped(m->regex, r_i) && \
			!(m->regex[r_i + 1] == '*'))
		return (func_star(m, m_i, r_i));
	if (m->regex[r_i] == '*' && !char_is_escaped(m->regex, r_i) && \
			(m->regex[r_i + 1] == '*'))
		return (match(m, m_i, r_i + 1));
	if (m->regex[r_i] == '?' && !char_is_escaped(m->regex, r_i))
		return (match(m, m_i + 1, r_i + 1));
	if (m->regex[r_i] == '[' && valid_square_bracket(m->regex, r_i))
	{
//		printf("valid\n");
		return (func_square_bracket(m, m_i, r_i));
	}
//	printf("invalid\n");
	return (func_cmp(m, m_i, r_i));
}
