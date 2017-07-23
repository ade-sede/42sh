/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   completion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vcombey <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/06/08 23:21:43 by vcombey           #+#    #+#             */
/*   Updated: 2017/06/08 23:21:48 by vcombey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPLETION_H
# define COMPLETION_H
# include "line_editing.h"
# include <dirent.h>

typedef struct		s_comple
{
	char		**matches;
	int		pos;
	int		signum;
	size_t		ws_col;
	size_t		max_len;
	size_t		nb_lines;
	size_t		nb_colones;
	size_t		nb_matches;
	char		*to_replace;
}			t_comple;

t_comple	*singleton_comple(void);

typedef struct		s_comple_func
{
	unsigned long long	keycode;
	int			(*f)(t_comple *);
}			t_comple_func;
/*
** signaux
*/
void	comple_set_signals(void);
void	comple_handle_sigwinch(t_line *line, t_comple *c);
void	comple_handle_sigint(t_line *line, t_comple *c);

int	comple_init(t_line *line, t_comple *c);
int	comple_init_winch(t_comple *c);
int	comple_get_input(t_line *line);
char	**comple_file_matches(t_line *line);

int		comple_right(t_comple *c);
int		comple_left(t_comple *c);
int		comple_up(t_comple *c);
int		comple_down(t_comple *c);

int	comple_refresh(t_line *line, t_comple c);

void	comple_clear(t_comple c);
void	comple_free(t_comple c);
int	comple_exit_matched(t_line *line, t_comple c);

# endif
