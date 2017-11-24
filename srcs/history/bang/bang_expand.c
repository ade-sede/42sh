/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bang_expand.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/24 17:54:27 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/24 19:22:53 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bang.h"
#include "libft.h"
#include "history.h"
#include "printf.h"

/*
**	PARAMS:
**		Source is the string we want to expand
**		Hist is the superhistory structure **
**	RETURN VALUE:
**		NULL if an error occured.
**		The address of the new expanded string otherwise.  **
**	Each function is incharge of the init for the variable it uses.
**	If everything was okay, this function frees everything when going out of
**	the loop, otherwise, each function is responsible for its memory.
*/

static int	error_routine(const char *error_msg, t_word *ret, t_word *onemore)
{
	ft_dprintf(2, "%s\n", error_msg);
	w_free(ret);
	if (onemore)
		w_free(onemore);
	return (0);
}

static int	wrapper_exec(const char **source, const char *s, \
		t_word *ret, t_hist *hist)
{
	t_word		event;
	t_word		word_designator;

	if (event_expand(s, source, &event, hist))
		return (error_routine("BAD EVENT", ret, NULL));
	if (word_designator_expand(source, event, &word_designator))
		return (error_routine("BAD WORD", ret, &event));
	w_free(&event);
	if (modifier_expand(source, ret, word_designator))
		return (error_routine("BAD MODIFIER", ret, &word_designator));
	w_free(&word_designator);
	return (1);
}

char		*bang_expand(const char *source, t_hist *hist)
{
	t_word		ret;
	int			state[2];
	const char	*s;

	state[_B_STATE] = DEF;
	state[_B_COUNT] = 0;
	s = source;
	w_newword(&ret);
	while (*source)
	{
		update_state(state, *source);
		if (state[_B_STATE] != BS && state[_B_STATE] != DQUOTES_BANG_BS_BANG \
				&& state[_B_STATE] != QUOTES_BANG \
				&& *source == '!' && !ft_strchr(" 	\n=(", *(source + 1)))
		{
			++source;
			if (!(wrapper_exec(&source, s, &ret, hist)))
				return (NULL);
		}
		w_addchar(&ret, *source);
		++source;
	}
	return (ret.str);
}
