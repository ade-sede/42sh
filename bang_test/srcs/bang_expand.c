#include "bang.h"
//#include "failure.h"
#include "libft.h"
#include "printf.h"

/*
**	PARAMS:
**		Source is the string we want to expand
**		Hist is the superhistory structure
**
**	RETURN VALUE:
**		NULL if an error occured.
**		The address of the new expanded string otherwise.  **
**	Each function is incharge of the init for the variable it uses.
**	If everything was okay, this function frees everything when going out of
**	the loop, otherwise, each function is responsible for its memory.
*/

static void change_state(int state[2], int s)
{
	state[_B_STATE] = s;
	state[_B_COUNT] = 0;
}


#include <stdio.h>
static int	update_state_part_1(int state[2], const char source)
{
	if (state[_B_STATE] == DEF)
	{
		if (source == '\'')
			change_state(state, QUOTES); else if (source == '"')
			change_state(state, DQUOTES);
		else if (source == '\\')
			change_state(state, BS);
		return (1);
	}
	if (state[_B_STATE] == QUOTES)
	{
		if (source == '\'')
			change_state(state, DEF);
		return (1);
	}
	return (0);
}
static void	update_state(int state[2], const char source)
{
	int	ret;

	ret = update_state_part_1(state, source);
	if (!ret)
	{
		if (state[_B_STATE] == DQUOTES)
		{
			if (source == '"')
				change_state(state, DEF);
			if (source == '\\')
				change_state(state, DQUOTES_BS);
		}
		else if (state[_B_STATE] == BS)
		{
			if (state[_B_COUNT] == 2)
				change_state(state, DEF);
		}
		else if (state[_B_STATE] == DQUOTES_BS)
			change_state(state, DQUOTES);
	}
	state[_B_COUNT]++;
}

char	*bang_expand(const char *source, t_hist *hist)
{
	(void)hist;
	t_word	ret;
	t_word	event;
	t_word	word_designator;
	int		err;
	int		state[2];
	int		done;
	const char	*s;

	/* NEED TO INCLUDE DEF BEHAVIOR IN THE FUNCTIONS THEMSELVES */
	change_state(state, DEF);
	s = source;
	w_newword(&ret);
	while (*source)
	{
		update_state(state, *source);
		if (state[_B_STATE] != BS && state[_B_STATE] != DQUOTES_BS && state[_B_STATE] != QUOTES && *source == '!' && !ft_strchr(" 	\n=(", *(source + 1)))
		{
			dprintf(2, "Found valid expand on index : %zu\n", source - s);
			/* Find event */
			++source;
			if ((err = event_expand(s, &source, &event, hist, &done)))
			{
				dprintf(2, "BAD EVENT\n");
				w_free(&ret);
				return (NULL);
			}
			/* Find word designator */
			dprintf(2, "%p\n", event.str);
			if ((err = word_designator_expand(&source, event, &word_designator, &done)))
			{
				dprintf(2, "BAD WORD\n");
				w_free(&ret);
				w_free(&event);
				return (NULL);
			}
			w_free(&event);
			if ((err = modifier_expand(&source, &ret, word_designator, &done)))
			{
				dprintf(2, "BAD MOD\n");
				w_free(&ret);
				w_free(&word_designator);
				return (NULL);
			}
			w_free(&word_designator);
		}
		w_addchar(&ret, *source);
		++source;
	}
	return (ret.str);
}
