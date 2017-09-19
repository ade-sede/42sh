#ifndef GLOB_STRUCT_H
# define GLOB_STRUCT_H

typedef	struct	s_matches
{
	t_list	*list;
	char	*to_match;
	char	*regex;
	char	*dir;
}				t_matches;

#endif
