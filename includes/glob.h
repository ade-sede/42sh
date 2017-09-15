#ifndef GLOB_H
#define GLOB_H

#include "libft.h"

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
void	curly_brackets_range_alpha(t_list **res, char *expr, char *str, int end);
void	curly_brackets_range_num(t_list **res, char *expr, char *str, int end);
void	curly_brackets_range(t_list **res, char *expr, char *str, int end);
int	curly_brackets_is_range(char *str);
char	**ft_strsplit_coma_bracket(char *expr);
int	ft_is_start_of_digit(char c);
#endif
