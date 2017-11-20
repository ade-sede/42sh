#include "bang.h"
#include "libft.h"

typedef	struct	s_hist
{
}				t_hist;

t_word	expand_event(const char **source, t_hist *hist, int *err)
{
	t_word	event;

	w_newword(&event);
	if (**source != '!' )
		*err = TRUE;
	++(*source);
	if (**source == 
	return (event);
}

char	*bang_expand(const char *source, t_hist *hist)
{
	t_word	ret;
	t_word	event;
	t_word	word_designator;
	int		err = FALSE;

	w_newword(&ret);
	while (*source)
	{
		while (*source && *source != '!')
		{
			w_addchar(&ret, *source);
			++source;
		}
		event = expand_event(&source, hist, &err);
		if (err == )
			return (NULL);
		word_designator = expand_word_designator(event, &source, &err);
		if (err)
			return (NULL);
		expand_modifier(word_designator, source, &ret);
		if (err)
			return (NULL);
	}
	return (ret.str);
}
