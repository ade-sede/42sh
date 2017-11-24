/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_token.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ade-sede <adrien.de.sede@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 20:53:05 by ade-sede          #+#    #+#             */
/*   Updated: 2017/11/23 20:55:09 by ade-sede         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexer.h"

static struct s_lex_action g_lex_action[] =
{
	{DEFAULT, &lex_action_default},
	{WORD, &lex_action_word},
	{WHITESPACE, &lex_action_whitespace},
	{QUOTES, &lex_action_quotes},
	{DQUOTES, &lex_action_dquotes},
	{BS, &lex_action_bs},
	{OPERATOR, &lex_action_operator},
	{NEWLINE, &lex_action_newline},
	{COMMENT, &lex_action_comment},
	{PARAM_EXP, &lex_action_param_exp},
	{AR_EXP, &lex_action_ar_exp},
	{CMD_SUBST, &lex_action_cmd_subst},
};

/*
**	PARAMS:
**		lex is the address of an existing lexer.
**
**	RETVAL:
**		If a token is created, returns the created token.
**		Otherwise (error, nothing to lex) return NULL.
*/

/*
** LOCAL_VAR:
** 		state_info is a cache. The last token or minitoken we delimited is
** 		storred.
**	Cycle of life :
**	Step 1 = Delimitation automata.  - Find the set of possible actions
**	corresponding to the current state.  - Within this set, find the exact
**	action corresponding to the given input.  - Work is done when we came back
**	to our original state and the last state we poped was complete (has an end
**	defined).
**	During delimitation of a token, we may enter different states, and delimit
**	"mini-tokens".
**	Step 2 = Token creation followed by token identification
*/

/*
**	In the natural flow, every new_value of state_info frees the precent one,
**	and the very last one is kept and used. If unnatural stop occurs, the last
**	value is not used, and must be freed manually.
*/

/*
**	Returning function pointer is tricky ...
*/

static int	(*get_action(ssize_t state))(t_lexer *, struct s_info **)
{
	size_t	i;

	i = 0;
	while (g_lex_action[i].state != state)
		++i;
	return (g_lex_action[i].func);
}

t_token		*get_token(t_lexer *lex)
{
	struct s_info	*state_info;
	t_token			*token;
	int				ret;

	ret = TRUE;
	token = NULL;
	state_info = NULL;
	while (ret)
	{
		if (((struct s_info*)lex->state->data)->state == DEFAULT)
			if (state_info && state_info->count != 0)
				break ;
		ret = get_action(((struct s_info*)lex->state->data)->state)\
			(lex, &state_info);
	}
	if (((struct s_info*)lex->state->data)->state == DEFAULT)
	{
		token = create_token(lex->line, state_info, lex->pos);
		get_token_id(lex, token);
	}
	else
		free_info(state_info);
	return (token);
}
