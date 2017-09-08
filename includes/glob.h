#ifndef GLOB_H
# define GLOB_H

# include "libft.h"
# include "list.h"

typedef	struct	s_matches
{
	t_list *list;
	char 	*to_match;
	char	*regex;
	char	*dir;
}		t_matches;

int	match_open_dir(t_matches *m, int to_match_i, int regex_i, char *dir_name);
int	match_open_file(t_matches *m, int to_match_i, int regex_i, char *file_name);
int	char_is_escaped(char *regex, int regex_i);
int	match(t_matches *m, int to_match_i, int regex_i);
int	match_open_dir(t_matches *m, int to_match_i, int regex_i, char *dir_name);
int	func_cmp(t_matches *m, int to_match_i, int regex_i);
int	func_star(t_matches *m, int to_match_i, int regex_i);
t_list	*glob(char *regex);
int	func_square_bracket(t_matches *m, int to_match_i, int regex_i);
int	valid_square_bracket(char *regex, int regex_i);
int	func_star(t_matches *m, int to_match_i, int regex_i);
int	func_cmp(t_matches *m, int to_match_i, int regex_i);
t_list	*expand_curly_brackets(char *expr);
void	curly_brackets(t_list **res, char *expr);
#endif
