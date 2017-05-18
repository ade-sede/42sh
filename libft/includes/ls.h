/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/19 13:10:40 by ade-sede          #+#    #+#             */
/*   Updated: 2017/04/08 14:22:24 by ade-sede         ###   ########.fr       */
/*   Updated: 2017/03/30 18:28:25 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef LS_H
# define LS_H
# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <sys/xattr.h>
# include <time.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include "libft.h"


typedef struct			s_ls_elem
{
	struct dirent		*dir_struct;
	struct s_ls_elem	*next;
	struct s_ls_elem	*prev;
	struct stat			stat;
	char				*arg_name;
	char				*mode_str; //		MALLOC'ED
	char				*time_str; //		MALLOC'ED
	int					file_size;
	int					nb_hard_links;
	struct passwd		*pw;
	struct group		*gr;
	int					is_syml;
	char				linked_name[4096];
	ssize_t				ln_size;
	char				*display_name; //	MALLOC'ED
	char				*true_path; //	MALLOC'ED
	int					is_dir;
	int					dont_display;
}						t_ls_elem;

typedef struct			s_ls_opt
{
	int					r_flag;
	int					l_flag;
	int					a_flag;
	int					t_flag;
	int					R_flag;
	int					s_flag;
	int					nb_arg;
}						t_ls_opt;

typedef struct			s_ls_arg
{ 
	struct s_ls_elem	*first;
	struct s_ls_elem	*last;
	struct s_ls_elem	*middle;
	char				*arg_name;
	int					index;
	struct s_ls_arg		*next;
	int					dont_display;
	int					is_syml;
	struct stat			stat;
	int					total;
	int					single_file;
	int					is_dir;
	int					nb_elem;
	int					pw_len;
	int					gr_len;
	int					bs_len;
	int					file_size_len;
	int					hard_link_len;
	int					shift_middle;
	int					error_code;
	struct s_list				*rec_first;
	int					is_empty;
}						 t_ls_arg;

void					ls_sort_insert_args(t_ls_opt *opt, t_ls_arg **first, t_ls_arg *new_arg);
void					ls_get_arg_info(t_ls_arg **arg);
int						ls_wrong_arg_pos(t_ls_opt *opt, t_ls_arg *ref_arg, t_ls_arg *new_arg);
void					ls_init_arg_head(t_ls_elem *elem, t_ls_arg **arg);
char					*get_d_name(char *str);
void					ls_get_display_len(t_ls_elem **elem, t_ls_arg **arg);
void					ls_test_arg(t_ls_arg **arg, t_ls_opt *opt);
void					ls_get_display_name(t_ls_elem **first, t_ls_opt *opt, t_ls_arg **arg);
void					ls_fill_stat(t_ls_elem **first, t_ls_opt *opt, t_ls_arg **arg);
t_ls_arg				*init_ls_arg(char *arg_name, int index);
t_ls_opt				init_ls_opt();
void					ls_arg_is_file(char *str, t_ls_arg **arg);
void					ls_arg_is_dir(char *str, DIR *dir, t_ls_opt *opt, t_ls_arg **arg);
void					fill_ls_elem(char *str, t_ls_arg **arg, DIR *dir, t_ls_opt *opt);
t_ls_elem				*init_ls_elem(char *arg_name, char *true_path, struct dirent *dir_struct);
char					*ls_file_mode(struct stat stat);
char					*ls_join_path(char *s1, char *s2);
t_ls_arg				*ls_parse(char **av, t_ls_opt *opt, int ac);
void					ls_get_opt(char *av, t_ls_opt *opt, t_ls_arg **arg);
void					ls_display(t_ls_elem *first, t_ls_opt *opt, t_ls_arg **arg, char *real_d_name);
void					error_ls(int error_code, char *error_string);
void					ft_ls(char *str, t_ls_opt *opt, t_ls_arg **arg);
void					ls_replace_middle(t_ls_arg **arg);
int						ls_time_sort(t_ls_elem* new_elem, t_ls_elem* ref_elem);
int						ls_alpha_sort(t_ls_elem* new_elem, t_ls_elem* ref_elem);
void					ls_sort_insert(t_ls_opt *opt, int (*f)(t_ls_elem*, t_ls_elem*), t_ls_arg **arg, t_ls_elem **elem);
void					ls_insert_after_last(t_ls_arg **arg, t_ls_elem **new_last);
void					ls_insert_after_middle(t_ls_arg **arg, t_ls_elem **elem, int (*f)(t_ls_elem*, t_ls_elem*));
void					ls_insert_before_middle(t_ls_arg **arg, t_ls_elem **elem, int (*f)(t_ls_elem*, t_ls_elem*));
void					ls_insert_before_first(t_ls_arg **arg, t_ls_elem **new_first);
#endif
