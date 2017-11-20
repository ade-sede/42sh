#include "bang.h"
#include "failure.h"
#include "libft.h"

/*
**	PARAMS:
**		Source is the string we want to expand
**		Hist is the superhistory structure
**
**	RETURN VALUE:
**		NULL if an error occured.
**		The address of the new expanded string otherwise.
**
**	Each function is incharge of the init for the variable it uses.
**	If everything was okay, this function frees everything when going out of
**	the loop, otherwise, each function is responsible for its memory.
*/

static void	update_state(int state[2], const char source)
{
	state[_B_COUNT]++;
	if (state
}

char	*bang_expand(const char *source, t_hist *hist)
{
	(void)hist;
	t_word	ret;
	t_word	event;
	t_word	word_designator;
	int		err;
	int		state[2];

	w_newword(&ret);
	while (*source)
	{
		update_state(state, *source);
		if (*source == '!' && !ft_strchr(" 	\n=(", *(source + 1)))
		{
			/* Find event */
			++source;
			if ((err = event_expand(&source, &event, hist)))
			{
				w_free(&ret);
				return ((void*)(long)investigate_error(1, "42sh", "Bad event", 0));
				/* Display error and return NULL */
			}
			/* Find work designator */
			/* Apply modifier */
			/* Free everything we used*/
			w_free(&event);
			w_free(&word_designator);
		}
		w_addchar(&ret, *source);
		++source;
	}
	return (ret.str);
}
