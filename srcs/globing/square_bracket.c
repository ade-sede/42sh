#include "glob.h"
#include <sys/dir.h>
#include <sys/types.h>
#include <dirent.h>

int	get_end_square_bracket(char *expr, int offset)
{
	int 	i;
	int		backslash;

	i = offset;
	i++;
	backslash = 0;
	if (expr[i] == '!')
		i++;
	if (expr[i] == ']')
		i++;
	while (expr[i])
	{
		if (expr[i] == ']' && backslash == 0)
			return (i);
		if (expr[i] == '\\')
			backslash = 1;
		else
			backslash = 0;
		i++;
	}
	return (-1);
}

int	valid_square_bracket(char *regex, int r_i)
{
	if (char_is_escaped(regex, r_i))
		return (0);
	if (get_end_square_bracket(regex, r_i) > 0)
		return (1);
	return (0);
}

int	match_square_bracket(char c, char *regex, int r_i, \
		int end_square_bracket)
{
	int	i;
	int	backslash;

	backslash = 0;
	i = r_i + 1;
	if (regex[i] == '!')
		i++;
	while (i < end_square_bracket)
	{
		if (backslash == 0 && regex[i + 1]  && regex[i + 2] && regex[i + 1] == '-')
		{
			if ((c >= regex[i] && c <= regex[i + 2]))
				return (1);
			i += 3;
			continue;
		}
		else if (regex[i] != '\\' && regex[i] == c)
			return (1);
		if (regex[i] == '\\')
			backslash = 1;
		else
			backslash = 0;
		i++;
	}
	return (0);
}

int	func_square_bracket(t_matches *m, int m_i, int r_i)
{
	int	exclamation;
	int	end_square_bracket;

	end_square_bracket = get_end_square_bracket(m->regex, r_i);
#ifdef GLOB_DEBUG
 printf("{%s}", ft_strsub(m->regex, r_i, end_square_bracket - r_i + 1));
 #endif
	exclamation = 0;
	if (m->regex[r_i + 1] == '!')
		exclamation = 1;
	if (!(m->to_match[m_i] == '.') && match_square_bracket(m->to_match[m_i], m->regex, r_i, \
				end_square_bracket) ^ exclamation)
		return (match(m, m_i + 1, end_square_bracket + 1));
	return (0);
}
