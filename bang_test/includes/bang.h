#ifndef BANG_H
# define BANG_H
# include "string.h"

#define _B_STATE 0
#define _B_COUNT 1

enum {
	DEF,
	QUOTES,
	DQUOTES,
	DQUOTES_BS,
	BS
};

typedef	struct	s_hist
{
}				t_hist;

/*
**	Returns represent erros. TRUE = error FALSE = ok
*/

/*
**	When parsing word designators, -3 is the uninit value
**	-1 is the last word.
**	-2 is the previous last.
*/

/*
**	
*/

char	*bang_expand(const char *source, t_hist *hist);
int		event_expand(const char *s, const char **source, t_word *event, t_hist *hist, int *done);
int		read_hist_numeric(int count, t_word *event, t_hist *hist);
int		word_designator_expand(const char **source, t_word event, t_word *word_designator, int *done);
int		modifier_expand(const char **source, t_word *ret, t_word word_designator, int *done);
#endif
