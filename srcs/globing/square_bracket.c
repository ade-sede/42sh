#include "glob.h"
#include <sys/dir.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

int	valid_square_bracket(char *regex, int regex_i)
{
	if (char_is_escaped(regex, regex_i))
		return (0);
	while (regex[regex_i] && regex[regex_i] != ']')
		regex_i++;	
	if (regex[regex_i] == ']' && !char_is_escaped(regex, regex_i))
		return (1);
	return (0);
}

int	match_square_bracket(char c, char *regex, int regex_i, int end_square_bracket)
{
	int	i;
	
	i = regex_i + 1;
	if (regex[i] == '!')
		i++;
	while (i < end_square_bracket)
	{
		if (regex[i + 1] == '-' && regex[i + 2] != '[')
		{
			if ((c >= regex[i] && c <= regex[i + 2])) 
				return (1);
			i += 3;
		}
		else if (regex[i] == c)
			return (1);
		else
			i++;
	}
	return (0);
}

int	func_square_bracket(t_matches *m, int to_match_i, int regex_i)
{
	int	i;
	int	exclamation;
	int	end_square_bracket;

	//printf("func square bracket to_match: %s, regex: %s\n", m->to_match + to_match_i, m->regex + regex_i);
	end_square_bracket = regex_i + ft_strichr(m->regex + regex_i, ']');
	i = regex_i + 1;
	exclamation = 0;
	if (m->regex[i] == '!')
	{
		exclamation = 1;
		i++;
	}
	if (match_square_bracket(m->to_match[to_match_i], m->regex, regex_i, end_square_bracket) ^ exclamation)
		return (match(m, to_match_i + 1, end_square_bracket + 1));
	//printf("func square bracket no match\n");
	return (0);
}
