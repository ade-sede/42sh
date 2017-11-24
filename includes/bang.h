/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 22:21:49 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 22:23:29 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BANG_H
# define BANG_H
# include "string.h"
# include "history.h"

# define _B_STATE 0
# define _B_COUNT 1

enum {
	DEF,
	QUOTES_BANG,
	DQUOTES_BANG,
	DQUOTES_BANG_BS_BANG,
	BS_BANG
};

/*
**	Returns represent erros. TRUE = error FALSE = ok
*/

/*
**	When parsing word designators, -3 is the uninit value
**	-1 is the last word.
**	-2 is the previous last.
*/

struct		s_parse_mod
{
	t_word	cache;
	t_word	tmp;
	int		quote_mode;
	int		g_flag;
};

void		pop(t_word *old, t_word *new);
void		init_p(struct s_parse_mod *p, t_word word_designator);
int			apply_quotes(struct s_parse_mod *p);
void		trunc_routines(const char **source, struct s_parse_mod *p);
int			substitute(const char **source, struct s_parse_mod *p);
void		lex_loop(const char *source, t_list **list);
int			extract_words(int start, int end, \
		t_word event, t_word *word_designator);
void		parse_end(const char **source, int *start, int *end);
void		parse_range(const char **source, int *start, int *end);
int			string_event(const char **source, t_word *event, t_hist *hist);
void		update_state(int state[2], const char source);
int			read_hist_numeric(int count, t_word *event, t_hist *hist);
int			read_hist_string(int flag, t_word string_event, \
		t_word *event, t_hist *hist);
char		*bang_expand(const char *source, t_hist *hist);
int			event_expand(const char *s, const char **source, \
		t_word *event, t_hist *hist);
int			word_designator_expand(const char **source, \
		t_word event, t_word *word_designator);
int			modifier_expand(const char **source, \
		t_word *ret, t_word word_designator);
#endif
