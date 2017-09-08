#include "glob.h"
#include <sys/dir.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>

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

int	func_cmp(t_matches *m, int to_match_i, int regex_i)
{
	if (m->regex[regex_i] == m->to_match[to_match_i])
		return (match(m, m->regex[regex_i] == '\\' ? to_match_i + 2 : to_match_i + 1, regex_i + 1));
	else
		return (0);
}

int	char_is_escaped(char *regex, int regex_i)
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
			break;
		regex_i--;
	}
	return (nb_bslash % 2);
}

int	match(t_matches *m, int to_match_i, int regex_i)
{
//condition d'arret
	//hprintf("to_match: %s, regex: %s\n", m->to_match + to_match_i, m->regex + regex_i);
	if (m->to_match[to_match_i] == '\0' && m->regex[regex_i] == '\0')		// sa a match
	{
		ft_simple_lst_add(&m->list, ft_simple_lst_create(ft_strdup(m->to_match)));
		// ft_lst_simple_create_add(&m->list, ft_strdup(m->to_match));
		return (1);
	}
	else if (m->to_match[to_match_i] == '\0' && m->regex[regex_i] != '\0' && m->regex[regex_i] != '*' && m->regex[regex_i] != '/') 
		return (0);
	//si on est pas a la fin de la regex soit c'est un / ou une etoile et on a encore sinon c'est mort
//fin de condition d'arret
	if (m->regex[regex_i] == '/' && m->to_match[to_match_i] == '\0')
		return (match_open_dir(m, to_match_i, regex_i + 1, ft_strdup(m->to_match)));
		//return (match_open_dir_change_dir(m, to_match_i, regex_i));
	if (m->regex[regex_i] == '*' && !char_is_escaped(m->regex, regex_i))
		return (func_star(m, to_match_i, regex_i));
	else if (m->regex[regex_i] == '[' && valid_square_bracket(m->regex, regex_i))
		return (func_square_bracket(m, to_match_i, regex_i));
	else if (m->regex[regex_i] == '?' && !char_is_escaped(m->regex, regex_i))
		return (match(m, to_match_i + 1, regex_i + 1)); //for the escaping 
	else if (m->regex[regex_i] != '\\' || (m->regex[regex_i] == '\\' && m->regex[regex_i + 1] == '\\')) //if 2// compare avec 1/ et match_i +=2;
		return (func_cmp(m, to_match_i, regex_i));
	else
		return (match(m, to_match_i, regex_i + 1)); //for the escaping 

}

t_list	*glob(char *regex)
{
	t_matches	m;
	char		*dir_name;
	size_t		regex_i;
	size_t		to_match_i;

	//m.list = NULL;
	//m.regex = regex;
	//m.to_match = NULL;
	dir_name = init_regex(regex, &regex_i);
	to_match_i = regex_i - 1;
	//m.dir = dir_name;
	m = (t_matches){NULL, NULL, regex, dir_name};
	//printf("dir_name: %s\n", dir_name);
	//if (ft_strequ(dir_name, "."))
	if (!match_open_dir(&m, to_match_i, regex_i, dir_name))
		return (ft_simple_lst_create(m.regex));
	return (m.list);
}
