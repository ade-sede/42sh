#ifndef BANG_H
# define BANG_H

#define _B_STATE
#define _B_COUNT

enum {
	DEF,
	QUOTES,
	DQUOTES,
	BS
}

typedef	struct	s_hist
{
}				t_hist;

char	*bang_expand(const char *source, t_hist *hist);
int		event_expand(const char **source, t_word *event, t_hist *hist);
#endif
