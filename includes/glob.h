/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   glob.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/18 14:05:46 by ade-sede          #+#    #+#             */
/*   Updated: 2017/09/18 14:06:00 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GLOB_H
# define GLOB_H
# include "libft.h"
# include "glob_struct.h"
# define IS_R(str) str[0] && str[1] && str[2] && str[3]
# define IS_RANGE_A(str) IS_R(str) && str[1] == '.' && str[2] == '.' && !str[4]

int		match_open_dir(t_matches *m, int to_match_i, int regex_i, \
		char *dir_name);
int		match_open_file(t_matches *m, int to_match_i, int regex_i, \
		char *file_name);
int		char_is_escaped(char *regex, int regex_i);
int		match(t_matches *m, int to_match_i, int regex_i);
int		match_open_dir(t_matches *m, int to_match_i, int regex_i, \
		char *dir_name);
int		func_cmp(t_matches *m, int to_match_i, int regex_i);
int		func_star(t_matches *m, int to_match_i, int regex_i);
int		func_square_bracket(t_matches *m, int to_match_i, int regex_i);
int		valid_square_bracket(char *regex, int regex_i);
int		func_star(t_matches *m, int to_match_i, int regex_i);
int		func_cmp(t_matches *m, int to_match_i, int regex_i);

t_list	*glob(char *regex);
t_list	*expand_curly_brackets(char *expr);
void	curly_brackets(t_list **res, char *expr);
void	curly_brackets_range_alpha(t_list **res, char *expr, char *str, \
		int end);
void	curly_brackets_range_num(t_list **res, char *expr, char *str, int end);
void	curly_brackets_range(t_list **res, char *expr, char *str, int end);
int		curly_brackets_is_range(char *str);
char	**ft_strsplit_coma_bracket(char *expr);
int		ft_is_start_of_digit(char c);
#endif
